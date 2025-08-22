#include <stdio.h>
#include "music_player.h"
#include "states/stopped_state.h"
#include "states/buffering_state.h"

/* Concrete: Stopped */
typedef struct {
    PlayerState base;
} StoppedState;

static void pressPlay(PlayerState *self) {
    printf("[Stopped] Nhấn Play: Bắt đầu phát nhạc…\n");
    music_player_change_state(self->player, buffering_state_instance());
}
static void pressPause(PlayerState *self) {
    (void)self;
    printf("[Stopped] Nhấn Pause: Không làm gì.\n");
}
static void pressStop(PlayerState *self) {
    (void)self;
    printf("[Stopped] Nhấn Stop: Đã dừng sẵn rồi.\n");
}

static const PlayerStateVTable VTABLE = {
    .pressPlay  = pressPlay,
    .pressPause = pressPause,
    .pressStop  = pressStop
};

PlayerState* stopped_state_instance(void) {
    static StoppedState instance;
    static int inited = 0;
    if (!inited) {
        instance.base.state = STATE_STOPPED;
        instance.base.vptr = &VTABLE;
        instance.base.player = NULL;
        inited = 1;
    }
    return (PlayerState*)&instance;
}
