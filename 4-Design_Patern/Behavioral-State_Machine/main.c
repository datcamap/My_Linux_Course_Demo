#include <stdio.h>
#include "music_player.h"
#include "stopped_state.h"

int main(void) {
    /* Khởi tạo với StoppedState */
    MusicPlayer *player = music_player_create(stopped_state_instance());
    if (!player) return 1;

    char command = 'a';
    while (command != 'q') {
        command = getchar();
        switch (command) {
        case 'c': {
            music_player_click_play(player);
            break;
        }
        case 'p': {
            music_player_click_pause(player);
            break;
        }
        case 's': {
            music_player_click_stop(player);
            break;
        }
        case 'q': {
            printf("Quiting.\n");
            break;
        }
        default: {
            printf("Please type in c, p, s, q \n");
            break;
        }
        }
    }

    music_player_destroy(player);
    return 0;
}
