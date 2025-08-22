#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include "player_state.h"

typedef struct MusicPlayer MusicPlayer;

/* API phía client */
MusicPlayer* music_player_create(PlayerState *initial_state);
void music_player_destroy(MusicPlayer *player);
void music_player_click_play(MusicPlayer *player);
void music_player_click_pause(MusicPlayer *player);
void music_player_click_stop(MusicPlayer *player);
void music_player_change_state(MusicPlayer *player, PlayerState *next);

#endif // MUSIC_PLAYER_H
