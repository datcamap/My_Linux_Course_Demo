#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <signal.h>

#define MAX_DISHES 10
#define MAX_PEOPLE 5
#define BUF_SIZE sizeof(bounded_buffer_t)

enum {
    EMPTY = 0,
    VEGAN,
    NON_VEGAN
};

typedef struct {
    int dish_type;
    char dish_name[50];
} dish_t;

typedef struct {
    dish_t dt[MAX_DISHES];
    int dish_count;
    sem_t mutex;
    sem_t empty;
    sem_t full;
} bounded_buffer_t;

void chef_Donatello(void);
void chef_Portecelli(void);
void consumer1(void);
void consumer2(void);
void consumer3(void);
void bb_init(bounded_buffer_t *bb);
void close_clean();

typedef void (*callback) (void);
callback table[MAX_PEOPLE] = {   chef_Donatello, \
                        chef_Portecelli, \
                        consumer1, \
                        consumer2, \
                        consumer3};

bounded_buffer_t *shared_non_vegan = NULL;
bounded_buffer_t *shared_vegan = NULL;

int main() 
{
    /* Signal for cleaning */
    signal(SIGINT, close_clean);

    shared_non_vegan = (bounded_buffer_t *)mmap(NULL, BUF_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_non_vegan == MAP_FAILED) {
        perror("shared_non_vegan can not be map.\n");
    }
    bb_init(shared_non_vegan);

    shared_vegan = (bounded_buffer_t *)mmap(NULL, BUF_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shared_vegan == MAP_FAILED) {
        perror("shared_vegan can not be map.\n");
    }
    bb_init(shared_vegan);

    int pid;

    for (int i = 0; i < MAX_PEOPLE; i++) {
        pid = fork();
        if (pid == 0) {
            table[i]();
            break;
        }
    }
    
    if (pid >0) {
        while(1) {
            printf("Non-vegan: %d/%d\n", shared_non_vegan->dish_count, MAX_DISHES);
            printf("Vegan: %d/%d\n", shared_vegan->dish_count, MAX_DISHES);
            sleep(10);
        }
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
        wait(NULL);
    }

    return 0;
}

void bb_init(bounded_buffer_t *bb)
{
    for (int i = 0; i < MAX_DISHES; i++) {
        bb->dt->dish_type = EMPTY;
    }
    bb->dish_count = 0;
    sem_init(&bb->mutex, 1, 1);
    sem_init(&bb->empty, 1, MAX_DISHES);
    sem_init(&bb->full, 1, 0);
}

void close_clean()
{
    sem_destroy(&shared_non_vegan->mutex);
    sem_destroy(&shared_non_vegan->empty);
    sem_destroy(&shared_non_vegan->full);

    sem_destroy(&shared_vegan->mutex);
    sem_destroy(&shared_vegan->empty);
    sem_destroy(&shared_vegan->full);
    
    munmap(shared_non_vegan, BUF_SIZE);
    munmap(shared_vegan, BUF_SIZE);
}

void chef_Donatello(void)
{
    printf("hi\n");
    const char *menu[] = {"Fettuccine Chicken Alfredo", \
                        "Garlic Sirloin Steak"};
    
    while(1) {
        const char *cooking_dish = menu[rand()%2];
        sem_wait(&shared_non_vegan->empty);
        for (int i = 0; i < MAX_DISHES; i++) {
            if (shared_non_vegan->dt[i].dish_type == EMPTY) {
                shared_non_vegan->dt[i].dish_type = NON_VEGAN;
                strcpy(shared_non_vegan->dt[i].dish_name, cooking_dish);
                printf("Donatello: cooked %s\n", shared_non_vegan->dt[i].dish_name);
                shared_non_vegan->dish_count++;
                break;
            }
        }
        sem_post(&shared_non_vegan->full);
        sleep(1 + rand()%5);
    }
}

void chef_Portecelli(void)
{
    const char *menu[] = {"Pistachio Pesto Pasta", \
                        "vocado Fruit Salad"};
    
    while(1) {
        const char *cooking_dish = menu[rand()%2];
        sem_wait(&shared_vegan->empty);
        for (int i = 0; i < MAX_DISHES; i++) {
            if (shared_vegan->dt[i].dish_type == EMPTY) {
                shared_vegan->dt[i].dish_type = NON_VEGAN;
                strcpy(shared_vegan->dt[i].dish_name, cooking_dish);
                printf("Portecelli: cooked %s\n", shared_vegan->dt[i].dish_name);
                shared_vegan->dish_count++;
                break;
            }
        }
        sem_post(&shared_vegan->full);
        sleep(1 + rand()%5);
    }
}

void consumer1(void)
{
    while(1) {
        sem_wait(&shared_non_vegan->mutex);
        for (int i = 0; i < MAX_DISHES; i++) {
            if (shared_non_vegan->dt[i].dish_type == NON_VEGAN) {
                shared_non_vegan->dt[i].dish_type = EMPTY;
                printf("Consumer #1: took %s\n", shared_non_vegan->dt[i].dish_name);
                shared_non_vegan->dish_count--;
                break;
            }
        }
        sem_post(&shared_non_vegan->empty);
        sem_post(&shared_non_vegan->mutex);

        sleep(10 + rand()%5);
    }
}

void consumer2(void)
{
    while(1) {
        sem_wait(&shared_vegan->mutex);
        for (int i = 0; i < MAX_DISHES; i++) {
            if (shared_vegan->dt[i].dish_type == NON_VEGAN) {
                shared_vegan->dt[i].dish_type = EMPTY;
                printf("Consumer #2: took %s\n", shared_vegan->dt[i].dish_name);
                shared_vegan->dish_count--;
                break;
            }
        }
        sem_post(&shared_vegan->empty);
        sem_post(&shared_vegan->mutex);

        sleep(10 + rand()%5);
    }
}

void consumer3(void)
{
    while(1) {
        sem_wait(&shared_non_vegan->mutex);
        for (int i = 0; i < MAX_DISHES; i++) {
            if (shared_non_vegan->dt[i].dish_type == NON_VEGAN) {
                shared_non_vegan->dt[i].dish_type = EMPTY;
                printf("Consumer #3: took %s\n", shared_non_vegan->dt[i].dish_name);
                shared_non_vegan->dish_count--;
                break;
            }
        }
        sem_post(&shared_non_vegan->empty);
        sem_post(&shared_non_vegan->mutex);

        sem_wait(&shared_vegan->mutex);
        for (int i = 0; i < MAX_DISHES; i++) {
            if (shared_vegan->dt[i].dish_type == NON_VEGAN) {
                shared_vegan->dt[i].dish_type = EMPTY;
                printf("Consumer #3: took %s\n", shared_vegan->dt[i].dish_name);
                shared_vegan->dish_count--;
                break;
            }
        }
        sem_post(&shared_vegan->empty);
        sem_post(&shared_vegan->mutex);

        sleep(10 + rand()%5);
    }
}