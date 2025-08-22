#ifndef HVAC_H
#define HVAC_H

typedef enum {
    HVAC_COOL, 
    HVAC_HEAT, 
    HVAC_AUTO, 
    HVAC_FAN_ONLY, 
    HVAC_OFF 
} HvacMode;

typedef struct HVAC HVAC;

typedef struct {
    void (*set_target_temp)(HVAC* self, float celsius);
    void (*set_mode)(HVAC* self, HvacMode mode);
} HVACOps;

struct HVAC {
    const HVACOps* ops;
    void* impl;
};

static inline void hvac_set_target_temp(HVAC* h, float c) 
{
    if (h && h->ops && h->ops->set_target_temp) {
        h->ops->set_target_temp(h, c);
    }
}
static inline void hvac_set_mode(HVAC* h, HvacMode m)
{
    if (h && h->ops && h->ops->set_mode) {
        h->ops->set_mode(h, m); 
    }
}

#endif // HVAC_H
