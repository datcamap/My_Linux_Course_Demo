#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <stdio.h>
#include "subscriber.h"

#define SUBSCRIBER_MAX 100

typedef struct Publisher Publisher_t;

struct Publisher {
    Subscriber_t* subscribe_list[SUBSCRIBER_MAX];
    int sub_count;

    void (*subscribe)(Publisher_t* ,Subscriber_t*);
    void (*unsubcribe)(Publisher_t*, Subscriber_t*);
    void (*notify)(Publisher_t*, const char*);
};

void publisher_init(Publisher_t* pub);

#endif // SUBSCRIBER_H