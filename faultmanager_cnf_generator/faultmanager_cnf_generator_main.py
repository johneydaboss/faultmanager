
from app.libs.faultmanager_cnf_classes import*
from app.generate.faultmanager_cnf_generate import*
import sys

"""
@brief
faultmanager cnf generator argument help menu
"""
def faultmanager_cnf_generator_help(args) -> str:
    msg = f"{args[0]} <option>\n"
    msg += "Available options:\n"
    msg += "\tgenerate: Generate the faultmanager_cnf_gen.c/h files\n"
    msg += "\thelp: shows this message\n"
    return msg


"""
@brief
main function
"""
def main():
    args = sys.argv
    if len(args) < 2:
        print(faultmanager_cnf_generator_help(args))
    
    elif (args[1] == 'generate'):
        try:
            faultmanager_cnf_generator(args=[args[0]] + args[2:])        
        except Exception as e:
            print("Exception: Failed faultmanager_cnf generation with following error ", e)
            sys.exit(-1)
    else:
        print(faultmanager_cnf_generator_help(args))
    return 0


if __name__ == "__main__":
    try:
        main()
    except:
        sys.exit(-1)