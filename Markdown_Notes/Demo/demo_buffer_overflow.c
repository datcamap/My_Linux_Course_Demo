#include <stdio.h>
#include <stdint.h>

int main()
{
    char my_name[10];
    scanf("%9s", my_name);  // Prevent buffer overflow
    printf("My name is %s \n\r", my_name);

    char outbuffer[5] = {};
    snprintf(outbuffer, sizeof(outbuffer) + 2, "This_is_a_very_long_text \n\r");
    // sprintf(outbuffer, "This_is_a_very_long_text \n\r");

    printf("%s", outbuffer);

    return 0;
}