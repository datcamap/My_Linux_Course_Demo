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
