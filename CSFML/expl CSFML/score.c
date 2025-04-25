#define _CRT_SECURE_NO_WARNINGS
#include "score.h"
#include <stdio.h>

void load_high_scores(int* high_scores) {
    FILE* file = fopen("../Ressources/highscores.txt", "r");
    if (file) {
        for (int i = 0; i < MAX_SCORES; i++) {
            if (fscanf(file, "%d", &high_scores[i]) != 1) {
                high_scores[i] = 0; // Valeur par d�faut si lecture �choue
            }
        }
        fclose(file);
    }
    else {
        // Si le fichier n'existe pas, initialiser � 0
        for (int i = 0; i < MAX_SCORES; i++) {
            high_scores[i] = 0;
        }
    }
}

void save_high_scores(int* high_scores) {
    FILE* file = fopen("../Ressources/highscores.txt", "w");
    if (file) {
        for (int i = 0; i < MAX_SCORES; i++) {
            fprintf(file, "%d\n", high_scores[i]);
        }
        fclose(file);
    }
}

void update_high_scores(int* high_scores, int new_score) {
    // Ajouter le nouveau score � la liste
    for (int i = 0; i < MAX_SCORES; i++) {
        if (new_score > high_scores[i]) {
            // D�caler les scores inf�rieurs vers la droite
            for (int j = MAX_SCORES - 1; j > i; j--) {
                high_scores[j] = high_scores[j - 1];
            }
            high_scores[i] = new_score;
            break;
        }
    }
    // Sauvegarder les scores mis � jour
    save_high_scores(high_scores);
}