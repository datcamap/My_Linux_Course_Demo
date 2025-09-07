#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int data = 0;
uint8_t data_ready = 0;
uint8_t production_completed = 0;
pthread_mutex_t producer_consumer_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_cond = PTHREAD_COND_INITIALIZER;
#define PRODUCING_LIMIT 10

void *thread_producer_handler(void* arg)
{
    if (arg != NULL) {
        int naptime = *(int *)arg;
        pthread_t _thd_id = pthread_self();
        printf("Hi! Thread %lu is the producer.\n", (unsigned long)_thd_id);

        for (int i = 0; i < PRODUCING_LIMIT; i++) {
            pthread_mutex_lock(&producer_consumer_mutex);
            data = rand()%100;
            printf("Producer %lu made the number %d.\n", (unsigned long)_thd_id, data);
            data_ready = 1;
            if(i % 2 == 1) {
                pthread_cond_signal(&data_cond);
            }
            pthread_mutex_unlock(&producer_consumer_mutex);
            //sleep(naptime);
        }

        production_completed = 1;
    }
    pthread_exit(NULL);
}

void *thread_consumer_handler(void* arg)
{
    pthread_mutex_lock(&producer_consumer_mutex);
    pthread_t _thd_id = pthread_self();
    printf("Hi! Thread %lu is the consumer.\n", (unsigned long)_thd_id);
    while(!production_completed || data_ready) {
        while (!data_ready) {
            //printf("Hello\n");
            pthread_cond_wait(&data_cond, &producer_consumer_mutex);
        }
        printf("Consumer %lu got the number %d.\n", (unsigned long)_thd_id, data);
        data_ready = 0;
        pthread_mutex_unlock(&producer_consumer_mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t th_producer_id, th_consumer_id;
    int naptime = 1;

    pthread_create(&th_consumer_id, NULL, &thread_consumer_handler, NULL);
    pthread_create(&th_producer_id, NULL, &thread_producer_handler, &naptime);

    pthread_join(th_producer_id, NULL);
    pthread_join(th_consumer_id, NULL);

    return 0;
}