#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIGNAL_TIMES 5

int counter = 0;

void sigusr1_callback()
{
    if (counter++ < SIGNAL_TIMES - 1) {
        printf("Received signal from parent.\n");
    } else {
        printf("Received SIGUSR1 %d times. Exiting now.\n", counter);
        exit(0);
    }
}

int main()
{
    int processID = fork();
    if (processID == 0) {
        signal(SIGUSR1, sigusr1_callback);
        while(1);
    } else if (processID > 0) {
        printf("My child's PID is %d\n", processID);
        for (int i = 0; i < SIGNAL_TIMES; i++) {
            sleep(2);
            kill(processID, SIGUSR1);
        }
        wait(NULL);
        printf("Child died. I'm out.\n");
    }

    return 0;
}