#include "render.h"
#include "player.h"
#include "pipes.h"
#include <SFML/Graphics.h>
#include <stdio.h>

void init_render(Game* game) {
    // Cette fonction est déjà gérée dans game.c pour charger les textures et sprites
    // Ici, on peut ajouter des initialisations supplémentaires si nécessaire
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

void draw_menu(sfRenderWindow* window, sfText* text) {
    sfText_setString(text, "Press ENTER to start");
    sfText_setCharacterSize(text, 40);
    sfText_setPosition(text, (sfVector2f) { WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 20 });
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(window, text, NULL);
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
    // Libérer les ressources
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