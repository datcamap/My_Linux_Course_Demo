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
    void*    user;     // optional: context riêng
} SensorConfig;

struct SensorOps {
    SensorStatus (*init)(Sensor* self, const SensorConfig* cfg);
    SensorStatus (*read)(Sensor* self, float* out_value);
    void         (*deinit)(Sensor* self);
    // mở rộng tùy nhu cầu:
    SensorStatus (*calibrate)(Sensor* self, int mode);
    const char*  (*unit)(Sensor* self); // "C", "%RH", "hPa", "lux", ...
};

struct Sensor {
    const SensorOps* ops;
    void*            impl;     // dữ liệu nội bộ của driver
};

static inline SensorStatus sensor_init(Sensor* s, const SensorConfig* c) {
    return s->ops->init ? s->ops->init(s, c) : SENSOR_ENOTSUP;
}
static inline SensorStatus sensor_read(Sensor* s, float* v) {
    return s->ops->read ? s->ops->read(s, v) : SENSOR_ENOTSUP;
}
static inline void sensor_deinit(Sensor* s) {
    if (s->ops->deinit) s->ops->deinit(s);
}
static inline const char* sensor_unit(Sensor* s) {
    return s->ops->unit ? s->ops->unit(s) : "";
}
