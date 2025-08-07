#include "moistureSensor.h"

/**
 * @brief Initializes a moisture sensor.
 *
 * @param[in] sensor_id     Sensor identifier.
 * @param[in] sensor_gpio   GPIO pin number.
 * @return Pointer to sensor, or NULL on failure.
 */
moisture_sensor_t *create_moisture_sensor(const uint8_t sensor_id, const uint8_t sensor_gpio)
{
    moisture_sensor_t *sensor = (moisture_sensor_t *)malloc(sizeof(moisture_sensor_t));
    if (sensor != NULL) {
        sensor->value = 0.0f;
        sensor->id = sensor_id;
        sensor->gpio = sensor_gpio;
    }
    return sensor;
}

/**
 * @brief Reads moisture data from the sensor.
 *
 * Simulates reading moisture data and returns it.
 *
 * @param[in] sensor    Pointer to the moisture sensor.
 * @return Moisture value, or -1.0f if sensor is NULL.
 */
float get_sensor_data(moisture_sensor_t *const sensor)
{
    if (sensor != NULL) {
        sensor->value = 100.0f*(float)rand()/(float)RAND_MAX; // Simulate reading moisture data
        printf("--- [Sensor ID: %d], [Moisture: %.2f%%] ---\n", sensor->id, sensor->value);
        return sensor->value;
    }
    return -1.0f; // Return an error value if sensor is NULL
}

/**
 * @brief Destroys the moisture sensor and frees allocated memory.
 *
 * @param[in] sensor  Pointer to the moisture sensor to be destroyed.
 */
void destroy_moisture_sensor(moisture_sensor_t *sensor)
{
    if (sensor != NULL) {
        free(sensor);
    }
}