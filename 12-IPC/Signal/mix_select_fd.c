#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/select.h>

#define BUF_SIZE 1024

int counter = 0;

void int_callback()
{
    printf("SIGINT received. \n");
}

void term_callback()
{
    printf("SIGTERM received. Exiting\n");
    exit(0);
}

int main()
{
    signal(SIGINT, int_callback);
    signal(SIGTERM, term_callback);

    while(1) {
        fd_set readfds;
        struct timeval timeout;
        FD_SET(STDIN_FILENO, &readfds);
        timeout.tv_sec = 5;
        if (select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout) > 0) {
            char buf[BUF_SIZE];
            if (fgets(buf, BUF_SIZE, stdin) != NULL) {
                printf("You entered: %s", buf);
            }
        }
    }

    return 0;
}