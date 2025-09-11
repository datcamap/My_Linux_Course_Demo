#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;

    connect(server_fd, (struct sockaddr *)&address, sizeof(address));

    char *msg = "Hello, server!";
    send(server_fd, msg, strlen(msg), 0);

    char buffer[128];
    recv(server_fd, buffer, sizeof(buffer)-1, 0);
    printf("Message from server: %s\n", buffer);

    close(server_fd);

    return 0;
}