#include <stdio.h>
#include <stdint.h>

typedef struct {
    uint32_t height;
    uint32_t width;
    uint8_t refresh_speed;
    char monitor_name[7];
} monitor1_t;

typedef struct {
    uint8_t refresh_speed;
    uint32_t height;
    uint32_t width;
    char monitor_name[7];
} monitor2_t;

typedef struct {
    uint8_t refresh_speed;
    uint32_t height;
    uint32_t width;
    char monitor_name[7];
} monitor3_t;

int main()
{    
    printf("monitor1_t memory size = %ld \n\r", sizeof(monitor1_t));
    printf("monitor2_t memory size = %ld \n\r", sizeof(monitor2_t));
    printf("monitor3_t memory size = %ld \n\r", sizeof(monitor3_t));

    return 0;
}