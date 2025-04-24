#pragma once


#include "game.h"

// Prototypes des fonctions pour le joueur
void init_player(Player* player, sfTexture* texture);
void update_player(Player* player, float delta_time, sfBool jump);
void draw_player(sfRenderWindow* window, Player* player);
void reset_player(Player* player);