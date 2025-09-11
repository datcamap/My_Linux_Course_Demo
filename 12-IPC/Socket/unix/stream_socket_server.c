#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BACK_LOG 10
#define SOCKET_PATH "/tmp/echo.sock"

int main()
{
    int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr_un address;
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCKET_PATH);

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