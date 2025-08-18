- Cấu trúc của state được thống nhất giữa các state, trong bài này là cấu trúc sau:

```C
    typedef struct PlayerStateVTable {
        void (*pressPlay)(struct PlayerState *self);
        void (*pressPause)(struct PlayerState *self);
        void (*pressStop)(struct PlayerState *self);
        const char* (*name)(struct PlayerState *self);
    } PlayerStateVTable;

    typedef struct PlayerState {
        const PlayerStateVTable *vptr;
        struct MusicPlayer *player;
    } PlayerState;
```

- Mỗi state cụ thể sẽ implement các thành phần của cấu trúc trên một cách khác nhau

Behavioral-State_Machine/
├── Makefile
├── main.c
├── inc/
│   ├── music_player.h
│   ├── player_state.h
│   └── states/
│       ├── buffering_state.h
│       ├── paused_state.h
│       ├── playing_state.h
│       └── stopped_state.h
└── src/
    ├── music_player.c
    └── states/
        ├── buffering_state.c
        ├── paused_state.c
        ├── playing_state.c
        └── stopped_state.c