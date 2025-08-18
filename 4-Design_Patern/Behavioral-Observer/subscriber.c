#include "subscriber.h"
#include <string.h>

static void subscriber_update(Subscriber_t* sub, const char* info)
{
    snprintf(sub->data, sizeof(sub->data),"Received: %s", info);
}

void subcriber_init(Subscriber_t* sub)
{
    if (sub == NULL) {
        return;
    }
    
    memset(sub->data, 0, sizeof(sub->data));
    sub->update = subscriber_update;
}
