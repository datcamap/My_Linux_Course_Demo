#include "actuator2.h"
#include <stdio.h>

static void actuator_act(void)
{
    printf("Actuator 2 is in action.\n");
}

void actuator2_init(Actuator2_t* act)
{
    act->action = actuator_act;
    subcriber_init(&act->base);
}