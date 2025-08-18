#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <stdio.h>

typedef struct Subscriber Subscriber_t;

struct Subscriber {
    char data[100];

    void (*update)(Subscriber_t*, const char*);
};

void subcriber_init(Subscriber_t* sub);

#endif // PUBLISHER_H