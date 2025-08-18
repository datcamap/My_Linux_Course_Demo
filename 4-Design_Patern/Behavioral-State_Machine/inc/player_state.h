#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

/* Forward declarations */
struct MusicPlayer;
struct PlayerState;

/* VTable cho "interface" PlayerState */
typedef struct PlayerStateVTable {
    void (*pressPlay)(struct PlayerState *self);
    void (*pressPause)(struct PlayerState *self);
    void (*pressStop)(struct PlayerState *self);
    const char* (*name)(struct PlayerState *self);
} PlayerStateVTable;

/* "Interface" PlayerState: có vptr + back-reference tới context */
typedef struct PlayerState {
    const PlayerStateVTable *vptr;
    struct MusicPlayer *player; /* context (được set khi change_state) */
} PlayerState;

#endif /* PLAYER_STATE_H */
