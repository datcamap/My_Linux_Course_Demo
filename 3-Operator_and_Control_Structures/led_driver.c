#include <string.h>
#include <stdlib.h>
#include "led_driver.h"
#include "logger.h"

int led_init(size_t num_pixels)
{
    led_strip.pixels = num_pixels;
    led_strip.led_buffer = (uint32_t *)malloc(num_pixels * sizeof(uint32_t));
    if (led_strip.led_buffer == NULL) {
        LOG_MESSAGE(LOG_ERROR, "Failed to allocate memory for LED buffer");
        return -1;
    }
    memset(led_strip.led_buffer, 0, num_pixels * sizeof(uint32_t)); // Initialize buffer to zero
    return 0; // Success
}

void led_shutdown()
{
    if (led_strip.led_buffer != NULL) {
        free(led_strip.led_buffer);
        led_strip.led_buffer = NULL;
    }
}

void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color = (g << 16) | (r << 8) | b; // Combine RGB into a single 32-bit value
    led_strip.led_buffer[index] = color;
}

void led_fill(uint8_t r, uint8_t g, uint8_t b)
{
    uint32_t color = (g << 16) | (r << 8) | b; // Combine RGB into a single 32-bit value
    for (size_t i = 0; i < led_strip.pixels; i++) {
        led_strip.led_buffer[i] = color;
    }
}

void led_clear()
{
    if (led_strip.led_buffer != NULL) {
        memset(led_strip.led_buffer, 0, led_strip.pixels * sizeof(uint32_t)); // Clear the buffer
    }
}

const uint32_t* led_get_buffer()
{
    return led_strip.led_buffer;
}

size_t led_get_pixel_count()
{
    return led_strip.pixels;
}