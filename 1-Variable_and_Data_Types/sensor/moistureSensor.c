#include "moistureSensor.h"
#include <stdio.h>
#include <stdlib.h>

MoistureSensor_t *createMoistureSensor(const uint8_t sensorID, const uint8_t sensor_GPIO)
{
    MoistureSensor_t *sensor = (MoistureSensor_t *)malloc(sizeof(MoistureSensor_t));
    if (sensor) {
        sensor->moisture = 0.0f; // Initialize moisture to 0
        sensor->sensorID = sensorID;
        sensor->sensor_GPIO = sensor_GPIO;
    }
    return sensor;
}

float getSensorData(MoistureSensor_t *const sensor)
{
    if (sensor) {
        sensor->moisture = 100.0f*(float)rand()/(float)RAND_MAX; // Simulate reading moisture data
        printf("Sensor ID: %d, Moisture: %.2f\n", sensor->sensorID, sensor->moisture);
        return sensor->moisture;
    }
    return -1.0f; // Return an error value if sensor is NULL
}

void destroyMoistureSensor(MoistureSensor_t *sensor)
{
    if (sensor) {
        free(sensor); // Free the allocated memory for the sensor
    }
}