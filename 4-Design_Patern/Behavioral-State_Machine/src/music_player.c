#include <stdio.h>
#include <stdlib.h>
#include "music_player.h"

struct MusicPlayer {
    PlayerState *current;
};

static void set_state(MusicPlayer *player, PlayerState *next) {
    player->current = next;
    next->player = player;
    printf("=> Trạng thái hiện tại: %s\n", state_str[player->current->state]);
}

MusicPlayer* music_player_create(PlayerState *initial_state) {
    MusicPlayer *mzkpl = (MusicPlayer*)malloc(sizeof(MusicPlayer));
    if (!initial_state || !mzkpl) {
        return NULL;
    }
    mzkpl->current = NULL;
    printf("=> Muzic player starting...\n");
    set_state(mzkpl, initial_state);
    return mzkpl;
}

void music_player_destroy(MusicPlayer *player) {
    if (!player) {
        return;
    }
    free(player);
}

void music_player_change_state(MusicPlayer *player, PlayerState *next) {
    if (!player || !next) {
        return;
    }
    set_state(player, next);
}

void music_player_click_play(MusicPlayer *player)
{
    player->current->vptr->pressPlay(player->current);
}
void music_player_click_pause(MusicPlayer *player)
{
    player->current->vptr->pressPause(player->current);
}
void music_player_click_stop(MusicPlayer *player)
{
    player->current->vptr->pressStop(player->current);
}
