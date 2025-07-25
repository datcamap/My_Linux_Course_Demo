#include <stdio.h>
#include <stdint.h>

typedef union {
    uint32_t IP;
    uint8_t IP_masked[4];
} IP_address;

int main()
{
    IP_address ip_addr;
    ip_addr.IP = 0xC0A80101;
    printf("IP_address memory size = %ld \n\r", sizeof(IP_address));
    printf("IP_address: %d.%d.%d.%d \n\r", 
        ip_addr.IP_masked[0], ip_addr.IP_masked[1], ip_addr.IP_masked[2], ip_addr.IP_masked[3]);
    printf("IP memory address: %p\n\r", &ip_addr.IP);
    printf("IP_masked memory address: %p-%p-%p-%p \n\r", 
        &(ip_addr.IP_masked[0]), &(ip_addr.IP_masked[1]), &ip_addr.IP_masked[2], &ip_addr.IP_masked[3]);

    return 0;
}