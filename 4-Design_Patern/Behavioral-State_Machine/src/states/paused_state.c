#include <stdio.h>
#include "music_player.h"
#include "paused_state.h"
#include "playing_state.h"
#include "stopped_state.h"

typedef struct {
    PlayerState base;
} PausedState;

static const char* name(PlayerState *self) { (void)self; return "Paused"; }

static void pressPlay(PlayerState *self) {
    printf("[Paused] Nhấn Play: Tiếp tục phát…\n");
    music_player_change_state(self->player, playing_state_instance());
}
static void pressPause(PlayerState *self) {
    (void)self;
    printf("[Paused] Nhấn Pause: Đã tạm dừng rồi.\n");
}
static void pressStop(PlayerState *self) {
    printf("[Paused] Nhấn Stop: Dừng và về đầu…\n");
    music_player_change_state(self->player, stopped_state_instance());
}

static const PlayerStateVTable VTABLE = {
    .pressPlay  = pressPlay,
    .pressPause = pressPause,
    .pressStop  = pressStop,
    .name       = name
};

PlayerState* paused_state_instance(void) {
    static PausedState instance;
    static int inited = 0;
    if (!inited) {
        instance.base.vptr = &VTABLE;
        instance.base.player = NULL;
        inited = 1;
    }
    return (PlayerState*)&instance;
}
