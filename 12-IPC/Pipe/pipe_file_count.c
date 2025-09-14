#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    int pid1, pid2;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == 0) { // Child 1
        printf("Executing 'ls -l' and write to output...\n");
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("ls", "ls -l", NULL);
        exit(1);
    } else if (pid1 > 0) { // Parent
        pid2 = fork();
        if (pid2 == 0) { // Child 2
            printf("Counting lines from 'ls -l' output...\n");
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            execlp("wc", "wc -l", NULL);
            exit(1);
        } else if (pid2 > 0) { // Parent
            close(fd[0]);
            close(fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}
