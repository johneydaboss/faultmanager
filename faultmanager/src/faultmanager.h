#ifndef FAULTMANAGER_H
#define FAULTMANAGER_H

#include "faultmanager_types.h"
#include "faultmanager_cnf_gen.h"
#include "Err_Def.h"

Err_T faultmanager_init(Fault* faults);
Err_T faultmanager_report_fault(uint32_t id, FaultStatus status);   

#endif // FAULTMANAGER_H