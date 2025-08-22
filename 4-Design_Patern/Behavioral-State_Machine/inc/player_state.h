#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

struct MusicPlayer;
struct PlayerState;

typedef enum {
    STATE_BUFFERING,
    STATE_PAUSED,
    STATE_PLAYING,
    STATE_STOPPED
} State_t;

static const char* state_str[] __attribute_maybe_unused__ = {
    "Buffering",
    "Paused",
    "Playing",
    "Stopped"
};

typedef struct PlayerStateVTable {
    void (*pressPlay)(struct PlayerState *self);
    void (*pressPause)(struct PlayerState *self);
    void (*pressStop)(struct PlayerState *self);
} PlayerStateVTable;

/* "Interface" PlayerState: có vptr + back-reference tới context */
typedef struct PlayerState {
    State_t state;
    const PlayerStateVTable *vptr;
    struct MusicPlayer *player; 
} PlayerState;

#endif // PLAYER_STATE_H
