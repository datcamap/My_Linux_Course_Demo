#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <unistd.h>

void bai1(void);
void bai2(char *argv_2);
void bai3(void);

static const char* command_line_args[] = {
    "bai1",
    "bai2",
    "bai3"
};

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], command_line_args[0]) == 0)) {
        bai1();
    }
    else if ( argc > 2 && (strcmp(argv[1], command_line_args[1]) == 0)) {
        bai2(argv[2]);
    }
    else if ( argc > 1 && (strcmp(argv[1], command_line_args[2]) == 0)) {
        bai3();
    }
    else {
        printf("No valid command line argument provided. Please use one of the following:\n %s\n %s\n %s\n", \
            command_line_args[0], command_line_args[1], command_line_args[2]);
    }

    return 0;
}

void bai1(void)
{
    int ret;
    ret = fork();
    if (ret == 0) {
        printf("I'm the child process. My PID is %d\n", getpid());
        exit(123);
    } else if (ret > 0) {
        while(1) {
            printf("I'm the parent process. My PID is %d and my child's PID is %d\n", getpid(), ret);
            sleep(5);
            int status, wait_ret;
            wait_ret = wait(&status);
            if (wait_ret == -1) {
                perror("Wait error\n");
                continue;
            }
            if (WIFEXITED(status)) {
                printf("Child process %d terminated with exit code %d\n", wait_ret, WEXITSTATUS(status));
                ret = 0;
                continue;
            } else {
                printf("Child process %d terminated abnormally\n", wait_ret);
            }
        }
    } else {
        perror("Forfeit\n");
    }
}

void bai2(char *argv_2)
{
    int ret;
    ret = fork();
    if (ret == 0) {
        printf("I'm the child process. My PID is %d\n", getpid());
        execlp(argv_2, argv_2, NULL);
        exit(123);
    } else if (ret > 0) {
        int status;
        wait(&status);
    } else {
        perror("Fork failed\n");
    }
}

void bai3(void) {}
