#include "systemConfig.h"
#include <stdlib.h>

static SystemConfig_t *configInstance = NULL;

SystemConfig_t *getSystemConfig(void)
{
    if (configInstance != NULL) {
        return configInstance; // Return the current system configuration
    }
    configInstance = (SystemConfig_t *)malloc(sizeof(SystemConfig_t));
    updateSystemConfig(SYSTEM_MODE_AUTO, 0.0f, 0.0f, 0, 0, 0); // Initialize with default values
    return configInstance;
}

SystemConfig_t *updateSystemConfig(SystemMode_t mode, 
                                   float moistureThresholdMIN, 
                                   float moistureThresholdMAX, 
                                   uint32_t pumpWaitTime, 
                                   uint32_t sensorReadInterval,
                                   uint32_t informingInterval)
{
    if (configInstance != NULL) {
        configInstance->mode = mode; // Initialize system mode
        configInstance->moistureThresholdMIN = moistureThresholdMIN; // Set minimum moisture threshold
        configInstance->moistureThresholdMAX = moistureThresholdMAX; // Set maximum moisture threshold
        configInstance->pumpWaitTime = pumpWaitTime; // Set pump wait time
        configInstance->sensorReadInterval = sensorReadInterval; // Set sensor read interval
        configInstance->informingInterval = informingInterval; // Set sensor read interval
    }
    return configInstance;
}

void destroySystemConfig(SystemConfig_t *config)
{
    if (config != NULL) {
        free(config); // Free the allocated memory for the system configuration
    }
}