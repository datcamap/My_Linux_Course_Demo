#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_un addr = {0};
    addr.sun_family = AF_UNIX;

    sendto(sockfd, "Hello", 5, 0, (struct sockaddr *)&addr, sizeof(addr));

    return 0;
}