#include <stdint.h>
#include <stdio.h>

typedef struct {
    uint32_t height;
    uint32_t width;
    uint8_t speed;
    //uint16_t brightness;
    char name[7];
} monitor1_t;

typedef struct {
    uint8_t speed;
    //uint16_t brightness;
    uint32_t height;
    uint32_t width;
    char name[7];
} monitor2_t;

typedef union {
    uint8_t speed;
    //uint16_t brightness;
    uint32_t height;
    uint32_t width;
    char name[7];
} monitor3_t;

typedef union {
    uint32_t IP;
    uint8_t IPmasked[4];
} IP_address;

typedef struct {
        uint8_t ODR : 4;
        uint8_t BDU : 1;
        uint8_t Zen : 1;
        uint8_t Yen : 1;
        uint8_t Xen : 1;
} CTRL_REG4;

int main()
{
    CTRL_REG4 powerreg;
    powerreg.ODR = 0b0101;
    powerreg.BDU = 0;
    powerreg.Zen = 1;
    powerreg.Yen = 1;
    powerreg.Xen = 1;

    IP_address ip_addr;
    ip_addr.IP = 0xC0A80101;

    printf("monitor1_t memory size = %ld \n\r", sizeof(monitor1_t));
    printf("monitor2_t memory size = %ld \n\r", sizeof(monitor2_t));
    printf("monitor3_t memory size = %ld \n\r", sizeof(monitor3_t));
    printf("IP_address memory size = %ld \n\r", sizeof(IP_address));
    printf("IP_address: %d.%d.%d.%d \n\r", 
        ip_addr.IPmasked[0], ip_addr.IPmasked[1], ip_addr.IPmasked[2], ip_addr.IPmasked[3]);

    printf("Memory address: %p-%p-%p-%p \n\r", 
        &(ip_addr.IPmasked[0]), &(ip_addr.IPmasked[1]), &ip_addr.IPmasked[2], &ip_addr.IPmasked[3]);
    
    int n = 1;
    
    if(*(char *)&n == 1) {printf("[Little Endian] \n\r");}
    else {printf("[Big Endian] \n\r");}
    
    // printBits(sizeof(powerreg), &powerreg);
    
    char myname[10];
    scanf("%s", myname);
    printf("My name is %s \n\r", myname);

    uint8_t outbuffer[5] = {};
    //sprintf(outbuffer, "This_is_a_very_long_text \n\r");
    snprintf(outbuffer, sizeof(outbuffer), "This1_is_a_very_long_text \n\r");
    printf("%s", outbuffer);

    return 0;
}