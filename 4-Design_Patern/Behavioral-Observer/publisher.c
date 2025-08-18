#include <string.h>
#include "publisher.h"

static void publisher_subscribe(Publisher_t* pub, Subscriber_t* sub);
static void publisher_unsubscribe(Publisher_t* pub, Subscriber_t* sub);
static void publisher_notify(Publisher_t* pub, const char* message);
static void remove_subscription(Publisher_t* pub, int sub_index);

static void publisher_subscribe(Publisher_t* pub, Subscriber_t* sub)
{   
    if (sub != NULL || pub != NULL) {
        if (pub->sub_count >= SUBSCRIBER_MAX) {
            printf("Maximum subcribe capacity reached.\n");
            return;
        }
        pub->subscribe_list[pub->sub_count++] = sub;
    }
}

static void publisher_unsubscribe(Publisher_t* pub, Subscriber_t* sub)
{
    if (sub != NULL || pub != NULL) {
        for (int i = 0; i < pub->sub_count; ++i) {
            if (pub->subscribe_list[i] == sub) {
                remove_subscription(pub, i);
                pub->sub_count--;
            }
        }
    }
}

static void remove_subscription(Publisher_t* pub, int sub_index)
{
    for (int i = sub_index; i  < (pub->sub_count - 1); ++i) {
        pub->subscribe_list[i] = pub->subscribe_list[i+1];
    }
}

static void publisher_notify(Publisher_t* pub, const char* message)
{
    if (pub == NULL) {
        return;
    }
    for (int i = 0; i < pub->sub_count; ++i) {
        pub->subscribe_list[i]->update(pub->subscribe_list[i], message);
    }
}

void publisher_init(Publisher_t* pub)
{
    if (pub == NULL) {
        return;
    }

    memset(pub->subscribe_list, 0, sizeof(pub->subscribe_list));
    pub->sub_count = 0;
    pub->subscribe = publisher_subscribe;
    pub->unsubcribe = publisher_unsubscribe;
    pub->notify = publisher_notify;
}