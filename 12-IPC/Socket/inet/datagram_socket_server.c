#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234

int main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    char buffer[128];
    struct sockaddr_in src;
    socklen_t srclen = sizeof(src);
    int n = recvfrom(sockfd, buffer, sizeof(buffer)-1, 0, (struct sockaddr *)&src, &srclen);
    buffer[n] = '\0';
    printf("Received: %s\n", buffer);
}