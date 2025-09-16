#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024
const char *shm_path = "/myshm";

int main() {

    int fd = shm_open(shm_path, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, BUF_SIZE); // allocate size
    void *shared_ptr = mmap(0, BUF_SIZE, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (shared_ptr == NULL) {
        perror("Failed to map shared mem\n");
    }

    printf("Input some text: \n");
    char buffer[BUF_SIZE + 1];
    fgets(buffer, BUF_SIZE, stdin);
    strcpy((char *)shared_ptr, buffer);
    printf("Producer write: \'%s\'\n", (char *)shared_ptr);

    sleep(10);

    close(fd);
    shm_unlink(shm_path); // remove shared memory
    return 0;
}