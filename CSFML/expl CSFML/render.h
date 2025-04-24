#pragma once


#include "game.h"

void init_render(Game* game);
void draw_background(sfRenderWindow* window, sfSprite* background);
void draw_ground(sfRenderWindow* window, sfSprite* ground);
void draw_score(sfRenderWindow* window, sfText* score_text, int score);
void draw_menu(sfRenderWindow* window, sfText* text);
void draw_game_over(sfRenderWindow* window, sfText* text, int score);
void cleanup_render(Game* game);

