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
    addr.sun_family = AF_INET;

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    char buffer[128];
    struct sockaddr_un src;
    socklen_t srclen = sizeof(src);
    int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&src, &srclen);
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);
}