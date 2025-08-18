#ifndef ACTUATOR1_H
#define ACTUATOR1_H

#include "subscriber.h"

typedef struct Actuator1 {
    Subscriber_t base;
    void (*action)(void);
} Actuator1_t;

void actuator1_init(Actuator1_t* act);

#endif // ACTUATOR1_H
