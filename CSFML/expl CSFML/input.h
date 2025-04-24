#pragma once


#include "game.h"

// Prototypes des fonctions pour les entrées
void handle_input(sfRenderWindow* window, Game* game, sfBool* jump);
void handle_menu_input(sfRenderWindow* window, Game* game);
void handle_game_over_input(sfRenderWindow* window, Game* game);

