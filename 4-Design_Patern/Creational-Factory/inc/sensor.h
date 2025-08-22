#include <stdint.h>

typedef struct Sensor Sensor;           // Handle opaque
typedef struct SensorOps SensorOps;

typedef enum {
    SENSOR_OK = 0,
    SENSOR_ERR = -1,
    SENSOR_ENOTSUP = -2,
    SENSOR_EBUS = -3,
} SensorStatus;

typedef struct {
    uint32_t bus_id;
    uint32_t dev_addr;
} SensorConfig;

struct Sensor {
    SensorConfig* _cfg;

    SensorStatus (*init)(Sensor* self, const SensorConfig* cfg);
    SensorStatus (*read)(Sensor* self, float* out_value);
    void         (*deinit)(Sensor* self);
    SensorStatus (*calibrate)(Sensor* self, int mode);
    const char*  (*unit)(Sensor* self); // "C", "%RH", "hPa", "lux", ...
};

static inline SensorStatus sensor_init(Sensor* s, const SensorConfig* c) {
    return s->init ? s->init(s, c) : SENSOR_ENOTSUP;
}
static inline SensorStatus sensor_read(Sensor* s, float* v) {
    return s->read ? s->read(s, v) : SENSOR_ENOTSUP;
}
static inline void sensor_deinit(Sensor* s) {
    return s->deinit ? s->deinit(s) : SENSOR_ERR;
}
static inline const char* sensor_unit(Sensor* s) {
    return s->unit ? s->unit(s) : "";
}
