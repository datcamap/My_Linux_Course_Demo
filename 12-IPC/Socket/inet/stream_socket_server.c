#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 1234
#define BACK_LOG 10

int main()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, BACK_LOG);

    int new_socket = accept(server_fd, NULL, NULL);     //Block until receive a client connection

    char *hello = "Hello from server";
    send(new_socket, hello, strlen(hello), 0);

    char buffer[128];
    recv(new_socket, buffer, sizeof(buffer)-1, 0);
    printf("Message from client: %s\n", buffer);
    
    close(new_socket);
    close(server_fd);

    return 0;
}