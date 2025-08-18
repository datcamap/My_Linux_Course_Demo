#include <stdio.h>
#include "music_player.h"
#include "buffering_state.h"
#include "playing_state.h"
#include "paused_state.h"
#include "stopped_state.h"

typedef struct {
    PlayerState base;
} BufferingState;

static const char* name(PlayerState *self) { (void)self; return "Buffering"; }

static void pressPlay(PlayerState *self) {
    printf("[Buffering] Nhấn Play: Đang tải… xong sẽ phát.\n");
    music_player_change_state(self->player, playing_state_instance());
    printf("Bắt đầu phát nhạc sau khi buffer xong.\n");
}
static void pressPause(PlayerState *self) {
    printf("[Buffering] Nhấn Pause: Hoãn phát sau khi tải xong.\n");
    music_player_change_state(self->player, paused_state_instance());
}
static void pressStop(PlayerState *self) {
    printf("[Buffering] Nhấn Stop: Hủy tải và dừng.\n");
    music_player_change_state(self->player, stopped_state_instance());
}

static const PlayerStateVTable VTABLE = {
    .pressPlay  = pressPlay,
    .pressPause = pressPause,
    .pressStop  = pressStop,
    .name       = name
};

PlayerState* buffering_state_instance(void) {
    static BufferingState instance;
    static int inited = 0;
    if (!inited) {
        instance.base.vptr = &VTABLE;
        instance.base.player = NULL;
        inited = 1;
    }
    return (PlayerState*)&instance;
}
