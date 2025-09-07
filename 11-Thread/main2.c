#include <stdio.h>
#include <pthread.h>

long long global_counter = 0;
#define COUNTING_LIMIT 3333333
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_handler(void* arg)
{
    pthread_t thd_id = pthread_self();
    for (long long this_thread_counter = 0; this_thread_counter < COUNTING_LIMIT; this_thread_counter++) {
        pthread_mutex_lock(&counter_mutex);
        pthread_t thd_id = pthread_self();
        printf("Thread %lu is increasing counter from %lld to %lld.\n", (unsigned long)thd_id, global_counter, ++global_counter);
        pthread_mutex_unlock(&counter_mutex);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id1, thread_id2, thread_id3;

    pthread_create(&thread_id1, NULL, &thread_handler, NULL);
    pthread_create(&thread_id2, NULL, &thread_handler, NULL);
    pthread_create(&thread_id3, NULL, &thread_handler, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);

    return 0;
}