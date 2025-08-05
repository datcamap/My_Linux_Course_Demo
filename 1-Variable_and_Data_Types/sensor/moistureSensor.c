#include "moistureSensor.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Initializes a moisture sensor.
 *
 * @param[in] sensor_ID     Sensor identifier.
 * @param[in] sensor_GPIO  GPIO pin number.
 * @return Pointer to sensor, or NULL on failure.
 */
Moisture_Sensor_t *create_moisture_sensor(const uint8_t sensorID, const uint8_t sensor_GPIO)
{
    Moisture_Sensor_t *sensor = (Moisture_Sensor_t *)malloc(sizeof(Moisture_Sensor_t));
    if (sensor) {
        sensor->moisture = 0.0f; // Initialize moisture to 0
        sensor->sensor_ID = sensorID;
        sensor->sensor_GPIO = sensor_GPIO;
    }
    return sensor;
}

/**
 * @brief Reads moisture data from the sensor.
 *
 * Simulates reading moisture data and returns it.
 *
 * @param[in] sensor  Pointer to the moisture sensor.
 * @return Moisture value, or -1.0f if sensor is NULL.
 */
float get_sensor_data(Moisture_Sensor_t *const sensor)
{
    if (sensor) {
        sensor->moisture = 100.0f*(float)rand()/(float)RAND_MAX; // Simulate reading moisture data
        printf("--- [Sensor ID: %d], [Moisture: %.2f%%] ---\n", sensor->sensor_ID, sensor->moisture);
        return sensor->moisture;
    }
    return -1.0f; // Return an error value if sensor is NULL
}

/**
 * @brief Destroys the moisture sensor and frees allocated memory.
 *
 * @param[in] sensor  Pointer to the moisture sensor to be destroyed.
 */
void destroy_moisture_sensor(Moisture_Sensor_t *sensor)
{
    if (sensor != NULL) {
        free(sensor); // Free the allocated memory for the sensor
    }
}