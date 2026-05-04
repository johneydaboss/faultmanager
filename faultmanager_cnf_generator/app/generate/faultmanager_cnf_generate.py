import json
import jinja2
import os
import hashlib
import sys
import argparse

from ..libs.faultmanager_cnf_classes import *

"""
@brief
Parses arguments provided to faultmanager cnf generator
"""
def faultmanager_cnf_generator_argparser():
    parser = None
    if( parser is None ):
        if( sys.version_info.minor >= 9):
            parser = argparse.ArgumentParser(description='FaultManager CNF GENERATOR',exit_on_error=True)
        else:
            parser = argparse.ArgumentParser(description='FaultManager CNF GENERATOR')
        parser.usage = "generate [-h] -c input_json_file -t template_path [template_list ...] [-o] output_files"
        parser.add_argument("-c","--cfg", nargs=1, required=True, help="FaultManager Configuration Json file" , dest="input_json_file")
        parser.add_argument("-t","--templates", nargs="+", required=True, help="List of template files" , dest="template_files")
        parser.add_argument("-o","--output", nargs="+", required=False, help="Output files", dest="output_files")
    return parser


"""
@brief
Generates faultmanager cnf files from templates and json file

Inputs: 
input_json_file: FAULTMANAGER_CNF.json with faultmanager configuration
template_files: list of template files to fill with data from json

Outputs: 
output_files: list of output files to be generates from templates
"""
def faultmanager_cnf_generator(args):
    
    ## --- Parse arguments --- 
    parsedArgs = faultmanager_cnf_generator_argparser().parse_args(args[1:])
    
    ## --- Assign arguments --- 
    input_file = parsedArgs.input_json_file[0]
    template_files = parsedArgs.template_files
    
    if parsedArgs.output_files:
        output_files = parsedArgs.output_files
        if len(output_files) != len(template_files):
            print("Error: There needs to be the same number of output files as template files")
            sys.exit(-1)
    else:
        output_files = []
        for template_file in template_files:
            name, extension = os.path.splitext(template_file)
            output_files.append(name + "_output" + extension)
    
    ## --- verify arguments --- 
    if os.path.isfile(input_file):
        for template in template_files:
            if not os.path.isfile(template):
                print("Error: template file ", template, " does not exist")
                sys.exit(-1)
    else:
        print("Error: input file ", input_file, " does not exist")
        sys.exit(-1)
    
    
    ## --- load data --- 
    faults_cnf =[]
    
    faultmanager_cnf = ["faults"]
    
    try:
        with open( input_file, "r") as f:
            data = json.load( f )
    except Exception as e:
        print("Exception: failed to load input json file with following error ", e)
        sys.exit(-1)

    ## --- verify data --- 
    for cnf in faultmanager_cnf:
        if cnf not in data:
            print("Error: missing", cnf, " from json file")
            sys.exit(-1)
    

    ## --- parse data --- 
  
    for fault in data["faults"]:
        faults_cnf.append(FaultConfig(**fault))
   
    ## --- render data and generate output file --- 
    for template_file, output_file in zip(template_files,output_files):
        
         # Render the channels into a output.c file using the dsadc_cnf_template.c as template using Jinja
        template_dir = os.path.dirname(os.path.abspath(template_file)) # Directory path
        template_name = os.path.basename(template_file)                # Just the file name!
        
        file_loader = jinja2.FileSystemLoader(template_dir)
        env = jinja2.Environment(loader=file_loader)
        
        template = env.get_template(template_name)
        
        output = template.render(faults = faults_cnf)
        try:       
            with open(output_file, 'w') as f:
                f.write(output)
                f.close()
        except Exception as e:
            print("Exception: Failed to write to output file with following error: ",e)
            sys.exit(-1)
    print("output files: ", output_files, "successfully generated")    
    return 0

