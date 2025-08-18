#include "sensor1.h"
#include "sensor2.h"
#include "sensor3.h"
#include "actuator1.h"
#include "actuator2.h"
#include "actuator3.h"

#define GPIO(x) x
#define ID(x) (char)x
#define BAUD_RATE(x) x

int main()
{
    Sensor1_t ss1;
    Sensor2_t ss2;
    Sensor3_t ss3; 
    sensor1_init(&ss1, ID(1), GPIO(1));
    sensor2_init(&ss2, ID(1), GPIO(2), BAUD_RATE(115200));
    sensor3_init(&ss3, ID(1), GPIO(3), GPIO(4));

    Actuator1_t act1;
    Actuator2_t act2;
    Actuator3_t act3;
    actuator1_init(&act1);
    actuator2_init(&act2);
    actuator3_init(&act3);

    ss1.base.subscribe(&ss1.base, &act1.base);
    
    ss2.base.subscribe(&ss2.base, &act1.base);
    ss2.base.subscribe(&ss2.base, &act2.base);

    ss3.base.subscribe(&ss3.base, &act1.base);
    ss3.base.subscribe(&ss3.base, &act2.base);
    ss3.base.subscribe(&ss3.base, &act3.base);

    ss1.base.notify(&ss1.base, "Message from the universe");

    return 0;
}