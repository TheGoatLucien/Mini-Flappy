#pragma once
#include <SFML/Graphics.h>

// Nombre de scores � sauvegarder
#define MAX_SCORES 7

// Prototypes des fonctions pour g�rer les scores
void load_high_scores(int* high_scores);
void save_high_scores(int* high_scores);
void update_high_scores(int* high_scores, int new_score);