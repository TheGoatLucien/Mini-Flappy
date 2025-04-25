#pragma once
#include "game.h"

// Prototypes des fonctions pour les tuyaux
void init_pipes(Pipe* pipes, int count, sfTexture* texture);
void update_pipes(Pipe* pipes, int count, float delta_time, Player* player, int* score, float* pipe_speed);
void draw_pipes(sfRenderWindow* window, Pipe* pipes, int count);
void reset_pipes(Pipe* pipes, int count);
sfBool check_collisions(Player* player, Pipe* pipes, int count);