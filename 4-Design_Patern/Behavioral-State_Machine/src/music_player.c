#include <stdio.h>
#include <stdlib.h>
#include "music_player.h"

struct MusicPlayer {
    PlayerState *current;
};

static void set_state(MusicPlayer *player, PlayerState *next) {
    player->current = next;
    next->player = player; /* thiết lập back-ref */
    printf("=> Trạng thái hiện tại: %s\n", player->current->vptr->name(player->current));
}

MusicPlayer* music_player_create(PlayerState *initial_state) {
    if (!initial_state) return NULL;
    MusicPlayer *p = (MusicPlayer*)malloc(sizeof(MusicPlayer));
    if (!p) return NULL;
    p->current = NULL;
    set_state(p, initial_state);
    return p;
}

void music_player_destroy(MusicPlayer *player) {
    if (!player) return;
    /* Không free state vì là singleton */
    free(player);
}

void music_player_change_state(MusicPlayer *player, PlayerState *next) {
    if (!player || !next) return;
    set_state(player, next);
}

/* Nút bấm phía client */
void music_player_click_play(MusicPlayer *player)  { player->current->vptr->pressPlay(player->current); }
void music_player_click_pause(MusicPlayer *player) { player->current->vptr->pressPause(player->current); }
void music_player_click_stop(MusicPlayer *player)  { player->current->vptr->pressStop(player->current); }
