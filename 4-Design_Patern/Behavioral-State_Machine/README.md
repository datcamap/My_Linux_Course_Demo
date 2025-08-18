Các state machine khác nhau thì các hàm có chức năng khác nhau luôn


Behavioral-State_Machine/
├── Makefile
├── main.c
├── include/
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