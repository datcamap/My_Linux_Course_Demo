#include <stdint.h>

typedef struct MoistureSensor {
    float moisture;
    uint8_t sensorID;
    uint8_t sensor_GPIO;
} MoistureSensor_t;

MoistureSensor_t *createMoistureSensor(uint8_t sensorID, uint8_t sensor_GPIO);
float getSensorData(MoistureSensor_t *const sensor);
void destroyMoistureSensor(MoistureSensor_t* sensor);