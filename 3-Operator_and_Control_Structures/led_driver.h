#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stdio.h>

typedef struct LED_strip {
    size_t pixels;
    uint32_t *led_buffer;
} LED_strip_t;

static LED_strip_t led_strip = {0, NULL};

int led_init(size_t num_pixels);
void led_shutdown();
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);
void led_fill(uint8_t r, uint8_t g, uint8_t b);
void led_clear();
const uint32_t* led_get_buffer();
size_t led_get_pixel_count();

#endif // LED_DRIVER_H