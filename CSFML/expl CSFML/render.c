#include "render.h"
#include <SFML/Graphics.h>
#include <stdio.h>

void init_render(Game* game) {
    sfText_setString(game->score_text, "0");
}

void draw_background(sfRenderWindow* window, sfSprite* background) {
    sfRenderWindow_drawSprite(window, background, NULL);
}

void draw_ground(sfRenderWindow* window, sfSprite* ground) {
    sfRenderWindow_drawSprite(window, ground, NULL);
}

void draw_score(sfRenderWindow* window, sfText* score_text, int score) {
    char score_str[16];
    snprintf(score_str, sizeof(score_str), "%d", score);
    sfText_setString(score_text, score_str);
    sfRenderWindow_drawText(window, score_text, NULL);
}

void draw_menu(sfRenderWindow* window, sfText* text, sfSprite* bird_sprite, int selected_bird) {
    // Instructions pour sélectionner l'oiseau
    sfText_setString(text, "Select your bird (Up/Down)\nPress ENTER to start");
    sfText_setCharacterSize(text, 30);
    sfText_setPosition(text, (sfVector2f) { WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 150 });
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(window, text, NULL);

    // Afficher les 7 oiseaux en colonne
    for (int i = 0; i < 7; i++) {
        sfSprite_setTextureRect(bird_sprite, (sfIntRect) { 0, i * 16, 16, 15 });
        sfSprite_setPosition(bird_sprite, (sfVector2f) { WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 50 + i * 30 });
        if (i == selected_bird) {
            sfSprite_setColor(bird_sprite, sfColor_fromRGB(255, 255, 0)); // Surligner l'oiseau sélectionné
        }
        else {
            sfSprite_setColor(bird_sprite, sfWhite);
        }
        sfRenderWindow_drawSprite(window, bird_sprite, NULL);
    }
}

void draw_game_over(sfRenderWindow* window, sfText* text, int score) {
    char game_over_str[64];
    snprintf(game_over_str, sizeof(game_over_str), "Game Over! Score: %d\nPress ENTER to restart", score);
    sfText_setString(text, game_over_str);
    sfText_setCharacterSize(text, 40);
    sfText_setPosition(text, (sfVector2f) { WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 40 });
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(window, text, NULL);
}

void cleanup_render(Game* game) {
    sfSprite_destroy(game->background);
    sfSprite_destroy(game->ground);
    sfText_destroy(game->score_text);
    sfFont_destroy(game->font);
    sfSprite_destroy(game->player->sprite);
    for (int i = 0; i < game->pipe_count; i++) {
        sfSprite_destroy(game->pipes[i].top_sprite);
        sfSprite_destroy(game->pipes[i].bottom_sprite);
    }
    free(game->player);
    free(game->pipes);
}