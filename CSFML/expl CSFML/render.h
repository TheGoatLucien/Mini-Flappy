#pragma once
#include "game.h"

void init_render(Game* game);
void draw_background(sfRenderWindow* window, sfSprite* current_background, sfSprite* next_background, float transition_timer);
void draw_ground(sfRenderWindow* window, sfSprite* ground);
void draw_score(sfRenderWindow* window, sfText* score_text, int score);
void draw_menu(sfRenderWindow* window, sfText* text, sfSprite* bird_sprite, int selected_bird, MenuSubState menu_substate, int* high_scores);
void draw_game_over(sfRenderWindow* window, sfText* text, int score);
void draw_high_scores(sfRenderWindow* window, sfText* text, int* high_scores);
void cleanup_render(Game* game);