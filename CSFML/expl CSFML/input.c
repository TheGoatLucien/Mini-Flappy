#include "input.h"
#include <SFML/Graphics.h>
#include <stdio.h>

void handle_input(sfRenderWindow* window, Game* game, sfBool* jump) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeySpace) {
                *jump = sfTrue; // Signal pour le saut du joueur
                printf("Jump triggered!\n"); // D�bogage
            }
        }
    }
}

void handle_menu_input(sfRenderWindow* window, Game* game) {
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed) {
            sfRenderWindow_close(window);
        }
        if (event.type == sfEvtKeyPressed) {
            if (event.key.code == sfKeyEnter) {
                game->state = PLAYING; // Passer � l'�tat de jeu
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
                reset_game(game); // R�initialiser pour une nouvelle partie
            }
        }
    }
}