#include "actuator1.h"
#include <stdio.h>

static void actuator_act(void)
{
    printf("Actuator 1 is in action.\n");
}

void actuator1_init(Actuator1_t* act)
{
    act->action = actuator_act;
    subcriber_init(&act->base);
}