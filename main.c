#include "faultmanager.h"
#include "faultmanager_cnf_gen.h"
#include <stdio.h>

int main(){
    faultmanager_init(fault_cnf);
    
    // Simulate some fault reports
    //faultmanager_report_fault(1, 1); // SensorFailure detected
    //faultmanager_report_fault(2, 1); // CommunicationError detected
    //faultmanager_report_fault(1, 0); // SensorFailure healed
    //faultmanager_report_fault(3, 1); // PowerFailure detected
    printf("Fault Manager initialized and fault reports simulated.\n");
    return 0;
}