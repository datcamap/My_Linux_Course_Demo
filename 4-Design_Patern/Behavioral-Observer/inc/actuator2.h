#ifndef ACTUATOR2_H
#define ACTUATOR2_H

#include "subscriber.h"

typedef struct Actuator2 {
    Subscriber_t base;
    void (*action)(void);
} Actuator2_t;

void actuator2_init(Actuator2_t* act);

#endif // ACTUATOR2_H
