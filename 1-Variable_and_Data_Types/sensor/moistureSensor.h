#include <stdint.h>

typedef struct Moisture_Sensor {
    float moisture;
    uint8_t sensor_ID;
    uint8_t sensor_GPIO;
} Moisture_Sensor_t;

Moisture_Sensor_t *create_moisture_sensor(uint8_t sensorID, uint8_t sensor_GPIO);
float get_sensor_data(Moisture_Sensor_t *const sensor);
void destroy_moisture_sensor(Moisture_Sensor_t* sensor);