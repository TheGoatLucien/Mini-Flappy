#include "input.h"
#include <SFML/Graphics.h>

void handle_input(sfRenderWindow* window, Game* game, sfBool* jump) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeySpace) {
                *jump = sfTrue;
            }
        }
    }
}

void handle_menu_input(sfRenderWindow* window, Game* game, int* selected_bird) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEnter) {
                game->player->selected_bird = *selected_bird;
                game->state = PLAYING;
            }
            if (event.key.code == sfKeyUp) {
                *selected_bird = (*selected_bird - 1 + 7) % 7; // Boucle entre 0 et 6
            }
            if (event.key.code == sfKeyDown) {
                *selected_bird = (*selected_bird + 1) % 7;
            }
        }
    }
}

void handle_game_over_input(sfRenderWindow* window, Game* game) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEnter) {
                reset_game(game);
            }
        }
    }
}