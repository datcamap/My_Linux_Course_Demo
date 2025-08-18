#include "actuator3.h"
#include <stdio.h>

static void actuator_act(void)
{
    printf("Actuator 3 is in action.\n");
}

void actuator3_init(Actuator3_t* act)
{
    act->action = actuator_act;
    subcriber_init(&act->base);
}