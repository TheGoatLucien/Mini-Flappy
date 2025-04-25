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
                sfSound_play(game->jump_sound); // Jouer le son de saut
            }
        }
    }
}

void handle_menu_input(sfRenderWindow* window, Game* game, int* selected_bird, MenuSubState* menu_substate) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (*menu_substate == MENU_BIRD_SELECTION) {
                if (event.key.code == sfKeyEnter) {
                    game->player->selected_bird = *selected_bird;
                    game->state = PLAYING;
                }
                if (event.key.code == sfKeyUp) {
                    *selected_bird = (*selected_bird - 1 + 7) % 7;
                }
                if (event.key.code == sfKeyDown) {
                    *selected_bird = (*selected_bird + 1) % 7;
                }
                if (event.key.code == sfKeyS) {
                    *menu_substate = MENU_HIGH_SCORES;
                }
            }
            else if (*menu_substate == MENU_HIGH_SCORES) {
                if (event.key.code == sfKeyS || event.key.code == sfKeyEscape) {
                    *menu_substate = MENU_BIRD_SELECTION;
                }
            }
        }
    }
}

void handle_game_over_input(sfRenderWindow* window, Game* game, sfBool* return_to_menu) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEnter) {
                reset_game(game);
            }
            if (event.key.code == sfKeyEscape) {
                *return_to_menu = sfTrue;
            }
        }
    }
}