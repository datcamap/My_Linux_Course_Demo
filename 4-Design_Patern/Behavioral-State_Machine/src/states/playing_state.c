#include <stdio.h>
#include "music_player.h"
#include "playing_state.h"
#include "paused_state.h"
#include "stopped_state.h"

typedef struct {
    PlayerState base;
} PlayingState;

static void pressPlay(PlayerState *self) {
    (void)self;
    printf("[Playing] Nhấn Play: Phát lại từ đầu (hoặc bỏ qua).\n");
}
static void pressPause(PlayerState *self) {
    printf("[Playing] Nhấn Pause: Tạm dừng nhạc…\n");
    music_player_change_state(self->player, paused_state_instance());
}
static void pressStop(PlayerState *self) {
    printf("[Playing] Nhấn Stop: Dừng phát…\n");
    music_player_change_state(self->player, stopped_state_instance());
}

static const PlayerStateVTable VTABLE = {
    .pressPlay  = pressPlay,
    .pressPause = pressPause,
    .pressStop  = pressStop
};

PlayerState* playing_state_instance(void) {
    static PlayingState instance;
    static int inited = 0;
    if (!inited) {
        instance.base.state = STATE_PLAYING;
        instance.base.vptr = &VTABLE;
        instance.base.player = NULL;
        inited = 1;
    }
    return (PlayerState*)&instance;
}
