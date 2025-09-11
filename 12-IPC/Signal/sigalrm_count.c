#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int counter = 0;

void alarm_callback()
{
    if (counter++ < 9) {
        alarm(1);
        printf("%d seconds passed.\n", counter);
    } else {
        printf("%d seconds passed. Exiting now.\n", counter);
        exit(0);
    }
}

int main()
{
    signal(SIGALRM, alarm_callback);
    alarm(1);
    
    while(1);

    return 0;
}