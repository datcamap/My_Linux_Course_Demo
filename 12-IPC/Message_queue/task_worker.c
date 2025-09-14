
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#define MAX_SIZE 1024
#define MAX_MESAGE 10
#define QUEUE_NAME "/task_Q"
const char *queue_name = "/task_Q";
mqd_t mess_q;

void cleaningup()
{
    printf("\nCleaning up and exiting...\n");
    mq_close(mess_q);
    mq_unlink(queue_name);
    exit(0);
}

int main()
{
    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESAGE;
    attr.mq_msgsize = MAX_SIZE;

    mess_q = mq_open(queue_name, O_CREAT | O_RDONLY, 0644,  &attr);
    if (mess_q == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    printf("Waiting for messages...\n");

    signal(SIGINT, cleaningup);

    char buffer[MAX_SIZE + 1];
    while (1) {
        int msg_prio;
        ssize_t bytes_read = mq_receive(mess_q, buffer, MAX_SIZE, &msg_prio);
        if (bytes_read >= 0) {
            buffer[bytes_read] = '\0';
            printf("(Priority: %d): %s\n", msg_prio, buffer);
            if (strcmp(buffer, "exit") == 0) {
                break;
            }
            sleep(10); // Simulate task processing time
        } else {
            perror("mq_receive");
        }
    }

    cleaningup();
    return 0;
}