#include <stdint.h>

typedef enum SystemMode {
    SYSTEM_MODE_AUTO,
    SYSTEM_MODE_MANUAL,
    SYSTEM_MODE_ERROR
} SystemMode_t;

typedef struct SystemConfig {
    SystemMode_t mode; // Current system mode
    float moistureThresholdMIN; // Minimum threshold for moisture sensor
    float moistureThresholdMAX; // Minimum threshold for moisture sensor
    uint32_t pumpWaitTime; // Wait time for pump operation in seconds
    uint32_t sensorReadInterval; // Interval for reading sensor data in seconds
    uint32_t informingInterval; // Interval for reading sensor data in seconds
} SystemConfig_t;

SystemConfig_t *createSystemConfig( SystemMode_t mode, 
                                    float moistureThresholdMIN, 
                                    float moistureThresholdMAX, 
                                    uint32_t pumpWaitTime, 
                                    uint32_t sensorReadInterval,
                                    uint32_t informingInterval);

void destroySystemConfig(SystemConfig_t *config);