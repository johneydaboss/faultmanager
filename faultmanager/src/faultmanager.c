#include "faultmanager.h"

static FaultManager fault_manager[NUM_FAULTS];

static Fault* fault_definitions;

Err_T faultmanager_init(Fault* faults) {
    Err_T err = ERR_OK;
    if(!faults){
        err = ERR_INVALID_PARAM; // Invalid fault definitions
    }
    else{
        fault_definitions = faults;
    
        for (int i = 0; i < NUM_FAULTS; i++) {
            fault_manager[i].confirm_counter = 0;
            fault_manager[i].heal_counter = 0;
            fault_manager[i].current_status = NoFault;
        }
    }
    return err;
}

static void handle_fault_action(FaultAction actions) {
    if ((actions & LogFault) != 0u) {
        // Implement logging logic here
    }

    if ((actions & NotifyUser) != 0u) {
        // Implement user notification logic here
    }

    if ((actions & ShutdownSystem) != 0u) {
        // Implement system shutdown logic here
    }
}

Err_T faultmanager_report_fault(uint32_t id, DiagResult status){
    
    Err_T err = ERR_OK;

    if (id >= NUM_FAULTS) {
        err = ERR_INVALID_PARAM; // Invalid fault ID
    }
    else if (status != DiagOK && status != DiagFailed) {
        err = ERR_INVALID_PARAM; // Invalid fault status
    }
    else{
        if(status == DiagFailed) { // Fault detected
            fault_manager[id].confirm_counter++;
            fault_manager[id].heal_counter = 0; // Reset heal counter
            
            if (fault_manager[id].confirm_counter == fault_definitions[id].confirmed_threshold) {
                fault_manager[id].current_status = FaultDetected;
                handle_fault_action(fault_definitions[id].actions);

                // Call the on_confirmed callback if defined
                if (fault_definitions[id].on_confirmed) {
                    fault_definitions[id].on_confirmed();
                }
            }
            else {
                fault_manager[id].current_status = Pending;
            }

        } else { // No fault
            fault_manager[id].heal_counter++;
            fault_manager[id].confirm_counter = 0; // Reset confirm counter
            
            if (fault_manager[id].heal_counter >= fault_definitions[id].heal_threshold) {
                fault_manager[id].current_status = NoFault;
            } else
            {
                fault_manager[id].current_status = Healing;
            }
        }
    }
    return err;
}   

Err_T getActiveFaults(Fault* active_faults, uint32_t* count) {
    Err_T err = ERR_OK;
    *count = 0;
    for (int i = 0; i < NUM_FAULTS; i++) {
        if (fault_manager[i].current_status == FaultDetected) {
            active_faults[*count] = fault_definitions[i];
            (*count)++;
        }
    }
    return err;
}

Err_T clearFault(uint32_t id) {
    Err_T err = ERR_OK;

    if (id < NUM_FAULTS) {
        fault_manager[id].confirm_counter = 0;
        fault_manager[id].heal_counter = 0;
        fault_manager[id].current_status = NoFault;
    }
    else{
        err = ERR_INVALID_PARAM; // Invalid fault ID
    }
    return err;
}

Err_T clearAllFaults() {
    Err_T err = ERR_OK;
    for (int i = 0; i < NUM_FAULTS; i++) {
        fault_manager[i].confirm_counter = 0;
        fault_manager[i].heal_counter = 0;
        fault_manager[i].current_status = NoFault;
    }
    return err;
}
