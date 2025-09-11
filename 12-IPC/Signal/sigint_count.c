#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int counter = 0;

void counting_callback()
{
    if (counter++ < 2) {
        printf("SIGINT received. \n");
    } else {
        printf("Received SIGINT %d times. Exiting now.\n", counter);
        exit(0);
    }
}

int main()
{
    signal(SIGINT, counting_callback);

    while(1);

    return 0;
}