#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h> 
#include <unistd.h>

#define BUF_SIZE 1024
const char *shm_path = "/myshm";

int main() {
    int shared_fd = shm_open(shm_path, O_RDONLY, 0666);
    void *ptr = mmap(0, BUF_SIZE, PROT_READ, MAP_SHARED, shared_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Failed to map shared mem\n");
    }

    fd_set readfds;
    struct timeval timeout;
    FD_ZERO(&readfds);
    FD_SET(shared_fd, &readfds); 
    timeout.tv_sec = 1;
    while (select(shared_fd + 1, &readfds, NULL, NULL, &timeout) == -1);
    printf("Consumer read: \'%s\'\n", (char*)ptr);

    close(shared_fd);
    return 0;
}