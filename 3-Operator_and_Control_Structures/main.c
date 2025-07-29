#include "led_driver.h"
#include "logger.h"

#define NUMBER_OF_PIXELS 10 // Example number of pixels

void print_led_strip_info()
{
    for (size_t i = 0; i < led_get_pixel_count(); i++) {
        printf("Pixel %zu color: R=0x%08X\n", i, led_get_buffer()[i]);
    }
}

int main()
{
    if (led_init(NUMBER_OF_PIXELS) != 0) {
        return -1; // Initialization failed
    }
    printf("LED strip initialized with %zu pixels.\n", led_get_pixel_count());
    print_led_strip_info();

    printf("Setting pixel 0 to Red color.\n");
    led_set_pixel_color(0, 255, 0, 0);
    printf("Setting pixel 9 to Blue color.\n");
    led_set_pixel_color(9, 0, 0, 255);
    printf("Setting pixel 4 to White color.\n");
    led_set_pixel_color(4, 255, 255, 255);
    print_led_strip_info();

    printf("Fill the strip with Green color. \n");
    led_fill(0, 255, 0);
    print_led_strip_info();

    // Shutdown the LED strip
    led_shutdown();

    return 0;
}