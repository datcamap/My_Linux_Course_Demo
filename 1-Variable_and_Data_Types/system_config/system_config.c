#include "system_config.h"
#include <stdlib.h>

static System_Config_t *config_instance = NULL;

/**
 * @brief Gets the current system configuration.
 *
 * If the configuration is not initialized, it creates a new instance
 * with default values.
 *
 * @return Pointer to the current system configuration.
 */
System_Config_t *get_system_config(void)
{
    if (config_instance != NULL) {
        return config_instance; // Return the current system configuration
    }
    config_instance = (System_Config_t *)malloc(sizeof(System_Config_t));
    update_system_config(SYSTEM_MODE_AUTO, 0.0f, 0.0f, 0, 0, 0); // Initialize with default values
    return config_instance;
}

/**
 * @brief Updates the system configuration with specified parameters.
 *
 * If the configuration instance is not initialized, it will be created.
 *
 * @param[in] sys_mode The system mode to set.
 * @param[in] moisture_thresholdMIN The minimum moisture threshold to set.
 * @param[in] moisture_thresholdMAX The maximum moisture threshold to set.
 * @param[in] pump_wait The pump wait time to set in seconds.
 * @param[in] sensor_read The sensor read interval to set in seconds.
 * @param[in] informing The informing interval to set in seconds.
 * @return Pointer to the updated system configuration.
 */
System_Config_t *update_system_config( System_Mode_t sys_mode, 
                                    float moisture_thresholdMIN, 
                                    float moisture_thresholdMAX, 
                                    uint32_t pump_wait, 
                                    uint32_t sensor_read,
                                    uint32_t informing)
{
    if (config_instance != NULL) {
        config_instance->mode = sys_mode; // Initialize system mode
        config_instance->moisture_threshold_MIN = moisture_thresholdMIN; // Set minimum moisture threshold
        config_instance->moisture_threshold_MAX = moisture_thresholdMAX; // Set maximum moisture threshold
        config_instance->pump_wait_time = pump_wait; // Set pump wait time
        config_instance->sensor_read_interval = sensor_read; // Set sensor read interval
        config_instance->informing_interval = informing; // Set sensor read interval
    }
    return config_instance;
}

/**
 * @brief Destroys the system configuration and frees allocated memory.
 *
 * This function should be called when the system configuration is no longer needed.
 *
 * @param config Pointer to the system configuration to be destroyed.
 */
void destroy_system_config(System_Config_t *config)
{
    if (config != NULL) {
        free(config); // Free the allocated memory for the system configuration
    }
}