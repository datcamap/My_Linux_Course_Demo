#ifndef SMART_HOME_FACADE_H
#define SMART_HOME_FACADE_H

#include "lighting.h"
#include "security.h"
#include "hvac.h"

typedef struct {
    int   bedroom_brightness;
    float comfort_temp;
    int   keep_perimeter_armed;
} SceneOptions;

typedef struct {
    Lighting* lighting;
    Security* security;
    HVAC*     hvac;
} SmartHomeFacade;

void facade_init(SmartHomeFacade* f, Lighting* l, Security* s, HVAC* h);

// high-level scenes
void facade_activate_morning_routine(SmartHomeFacade* f, const SceneOptions* opt);
void facade_activate_away_mode(SmartHomeFacade* f);
void facade_set_movie_night_scene(SmartHomeFacade* f);

// simple high-level knobs
void facade_set_room_brightness(SmartHomeFacade* f, const char* room, int pct);
void facade_set_comfort_temp(SmartHomeFacade* f, float c);

#endif // SMART_HOME_FACADE_H
