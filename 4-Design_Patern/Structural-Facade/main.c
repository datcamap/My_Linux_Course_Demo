#include "smart_home_facade.h"
#include <stdio.h>

// forward driver init prototypes (from the mock driver C files)
void lighting_driver_mock_init(struct Lighting* obj, void* storage);
void security_driver_mock_init(struct Security* obj, void* storage);
void hvac_driver_mock_init(struct HVAC* obj, void* storage);

typedef struct { int dummy; } ZigbeeLightingImpl;
typedef struct { int perimeter_armed; int cameras_on; } BasicSecurityImpl;
typedef struct { float target_c; int mode; } SimpleHVACImpl;

int main(void) {
    Lighting lighting;
    Security security;
    HVAC     hvac;

    ZigbeeLightingImpl light_impl;
    BasicSecurityImpl  sec_impl;
    SimpleHVACImpl     hvac_impl;

    lighting_driver_mock_init(&lighting, &light_impl);
    security_driver_mock_init(&security, &sec_impl);
    hvac_driver_mock_init(&hvac, &hvac_impl);

    SmartHomeFacade home;
    facade_init(&home, &lighting, &security, &hvac);

    // Morning routine (defaults)
    facade_activate_morning_routine(&home, NULL);

    // Custom options
    SceneOptions opt = { .bedroom_brightness = 70, .comfort_temp = 24.5f, .keep_perimeter_armed = 0 };
    facade_activate_morning_routine(&home, &opt);

    // Movie night
    facade_set_movie_night_scene(&home);

    // Away mode
    facade_activate_away_mode(&home);

    // High-level individual controls
    facade_set_room_brightness(&home, "Bedroom", 30);
    facade_set_comfort_temp(&home, 25.0f);

    return 0;
}
