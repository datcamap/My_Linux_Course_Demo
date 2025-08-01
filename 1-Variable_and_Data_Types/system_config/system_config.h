#include <stdint.h>

typedef enum System_Mode {
    SYSTEM_MODE_AUTO,
    SYSTEM_MODE_MANUAL,
    SYSTEM_MODE_ERROR
} System_Mode_t;

typedef struct System_Config {
    System_Mode_t mode; // Current system mode
    float moisture_threshold_MIN; // Minimum threshold for moisture sensor
    float moisture_threshold_MAX; // Minimum threshold for moisture sensor
    uint32_t pump_wait_time; // Wait time for pump operation in seconds
    uint32_t sensor_read_interval; // Interval for reading sensor data in seconds
    uint32_t informing_interval; // Interval for reading sensor data in seconds
} System_Config_t;

System_Config_t *get_system_config(void);
System_Config_t *update_system_config( System_Mode_t sys_mode, 
                                    float moisture_thresholdMIN, 
                                    float moisture_thresholdMAX, 
                                    uint32_t pump_wait, 
                                    uint32_t sensor_read,
                                    uint32_t informing);
void destroy_system_config(System_Config_t *config);