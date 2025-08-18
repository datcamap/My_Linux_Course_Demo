#ifndef ACTUATOR3_H
#define ACTUATOR3_H

#include "subscriber.h"

typedef struct Actuator3 {
    Subscriber_t base;
    void (*action)(void);
} Actuator3_t;

void actuator3_init(Actuator3_t* act);

#endif // ACTUATOR3_H