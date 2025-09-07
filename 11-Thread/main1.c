#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_handler(void* arg)
{
    if (arg != NULL) {
        int i = *(int *)arg;
        pthread_t thd_id = pthread_self();
        printf("Hello from the new thread %lu!\n", (unsigned long)thd_id);
        for (; i > 0; i--) {
            printf("Thread %lu exit after %ds.\n", (unsigned long)thd_id, i);
            sleep(1);
        }
        printf("Thread %lu is exiting.\n", (unsigned long)thd_id);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id1, thread_id2;
    int lapse1 = 5;
    int lapse2 = 15;
    pthread_create(&thread_id1, NULL, &thread_handler, &lapse1);
    pthread_create(&thread_id2, NULL, &thread_handler, &lapse2);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    printf("Thread main is exiting.\n");

    return 0;
}