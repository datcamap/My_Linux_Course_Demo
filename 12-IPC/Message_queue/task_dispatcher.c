
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE 1024
#define MAX_MESAGE 1024
const char *queue_name = "/task_Q";
mqd_t mess_q;

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <priority> <message>\n", argv[0]);
        exit(1);
    }

    int priority = atoi(argv[1]);
    const char *message = argv[2];

    struct mq_attr attr;
    attr.mq_maxmsg = MAX_MESAGE;
    attr.mq_msgsize = MAX_SIZE;

    mess_q = mq_open(queue_name, O_WRONLY, 0644,  &attr);
    if (mess_q == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }
    
    printf("Sending message: %s with priority %d\n", message, priority);

    if (mq_send(mess_q, message, strlen(message), priority) == -1) {
        perror("mq_send");
        mq_close(mess_q);
        exit(1);
    }

    return 0;
}