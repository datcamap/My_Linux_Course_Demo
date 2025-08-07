#ifndef system_config_H
#define system_config_H

#include <stdint.h>

typedef enum system_mode {
    system_mode_AUTO,
    system_mode_MANUAL,
    system_mode_ERROR
} system_mode_t;

typedef struct system_config {
    system_mode_t mode;             // Current system mode
    float moisture_threshold_min;   // Minimum threshold for moisture sensor
    float moisture_threshold_max;   // Minimum threshold for moisture sensor
    uint32_t pump_wait_time;        // Wait time for pump operation in seconds
    uint32_t reading_interval;  // Interval for reading sensor data in seconds
    uint32_t informing_interval;    // Interval for reading sensor data in seconds
} system_config_t;

system_config_t *get_system_config(void);
system_config_t *update_system_config( system_mode_t sys_mode, 
                                    float moisture_min, 
                                    float moisture_max, 
                                    uint32_t pump_wait, 
                                    uint32_t sensor_read,
                                    uint32_t informing);
void destroy_system_config(system_config_t *config);

#endif // system_config_H