#include "systemConfig.h"

SystemConfig_t *createSystemConfig(SystemMode_t mode, 
                                   float moistureThresholdMIN, 
                                   float moistureThresholdMAX, 
                                   uint32_t pumpWaitTime, 
                                   uint32_t sensorReadInterval,
                                   uint32_t informingInterval)
{
    SystemConfig_t *config = (SystemConfig_t *)malloc(sizeof(SystemConfig_t));
    if (config) {
        config->mode = mode; // Initialize system mode
        config->moistureThresholdMIN = moistureThresholdMIN; // Set minimum moisture threshold
        config->moistureThresholdMAX = moistureThresholdMAX; // Set maximum moisture threshold
        config->pumpWaitTime = pumpWaitTime; // Set pump wait time
        config->sensorReadInterval = sensorReadInterval; // Set sensor read interval
        config->informingInterval = informingInterval; // Set sensor read interval
    }
    return config;
}

void destroySystemConfig(SystemConfig_t *config)
{
    if (config) {
        free(config); // Free the allocated memory for the system config
    }
}