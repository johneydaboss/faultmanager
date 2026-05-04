#ifndef FAULTMANAGER_TYPES_H
#define FAULTMANAGER_TYPES_H

#include <stdint.h>

typedef enum FaultType {
    None,
    SensorFailure,
    CommunicationError,
    PowerFailure,
    Overheating,
    SoftwareError
} FaultType;

typedef enum FaultStatus {
    NoFault,
    Pending,
    Healing,
    FaultDetected
} FaultStatus;

typedef enum FaultAction {
    NoAction = 0u,
    LogFault = (1u << 0),
    NotifyUser = (1u << 1),
    ShutdownSystem = (1u << 2)
} FaultAction;

typedef enum FaultSeverity {
    Low = 1,
    Medium = 5,
    High = 10
} FaultSeverity;

typedef enum DiagResult {
    DiagOK,
    DiagFailed,
    DiagInProgress
} DiagResult;

typedef struct Fault {
    uint32_t id;
    FaultType type;
    FaultSeverity severity;
    uint8_t confirmed_threshold;
    uint8_t heal_threshold;
    void (*on_confirmed)(void);
    FaultAction actions;
}Fault;

typedef struct FaultManager {
    uint32_t confirm_counter;
    uint32_t heal_counter;
    FaultStatus current_status;
} FaultManager;

#endif // FAULTMANAGER_TYPES_H