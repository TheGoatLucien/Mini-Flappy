#include "render.h"
#include <SFML/Graphics.h>
#include <stdio.h>

void init_render(Game* game) {
    sfText_setString(game->score_text, "0");
}

void draw_background(sfRenderWindow* window, sfSprite* current_background, sfSprite* next_background, float transition_timer) {
    if (transition_timer < TRANSITION_DURATION) {
        // Crossfade : l'image actuelle diminue, la suivante augmente
        float alpha = transition_timer / TRANSITION_DURATION; // Va de 0 � 1
        sfSprite_setColor(current_background, sfColor_fromRGBA(255, 255, 255, (sfUint8)(255 * (1.0f - alpha))));
        sfSprite_setColor(next_background, sfColor_fromRGBA(255, 255, 255, (sfUint8)(255 * alpha)));
        sfRenderWindow_drawSprite(window, current_background, NULL);
        sfRenderWindow_drawSprite(window, next_background, NULL);
    }
    else {
        // Pas de transition, afficher l'image actuelle
        sfSprite_setColor(current_background, sfColor_fromRGBA(255, 255, 255, 255));
        sfRenderWindow_drawSprite(window, current_background, NULL);
    }
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

void draw_menu(sfRenderWindow* window, sfText* text, sfSprite* bird_sprite, int selected_bird, MenuSubState menu_substate, int* high_scores) {
    if (menu_substate == MENU_BIRD_SELECTION) {
        sfText_setString(text, "Select your bird (Up/Down)\nPress ENTER to start\nPress S to view high scores");
        sfText_setCharacterSize(text, 30);
        sfText_setPosition(text, (sfVector2f) { WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 150 });
        sfText_setColor(text, sfBlack);
        sfRenderWindow_drawText(window, text, NULL);

        for (int i = 0; i < 7; i++) {
            sfSprite_setTextureRect(bird_sprite, (sfIntRect) { 0, i * 16, 16, 15 });
            sfSprite_setPosition(bird_sprite, (sfVector2f) { WINDOW_WIDTH / 2 - 20, WINDOW_HEIGHT / 2 - 50 + i * 30 });
            if (i == selected_bird) {
                sfSprite_setColor(bird_sprite, sfColor_fromRGB(255, 255, 0));
            }
            else {
                sfSprite_setColor(bird_sprite, sfWhite);
            }
            sfRenderWindow_drawSprite(window, bird_sprite, NULL);
        }
    }
    else if (menu_substate == MENU_HIGH_SCORES) {
        draw_high_scores(window, text, high_scores);
    }
}

void draw_high_scores(sfRenderWindow* window, sfText* text, int* high_scores) {
    char high_scores_str[256];
    snprintf(high_scores_str, sizeof(high_scores_str),
        "High Scores\n1. %d\n2. %d\n3. %d\n4. %d\n5. %d\n6. %d\n7. %d\nPress S or ESC to return",
        high_scores[0], high_scores[1], high_scores[2], high_scores[3],
        high_scores[4], high_scores[5], high_scores[6]);
    sfText_setString(text, high_scores_str);
    sfText_setCharacterSize(text, 30);
    sfText_setPosition(text, (sfVector2f) { WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 150 });
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(window, text, NULL);
}

void draw_game_over(sfRenderWindow* window, sfText* text, int score) {
    char game_over_str[128];
    snprintf(game_over_str, sizeof(game_over_str), "Game Over! Score: %d\nPress ENTER to restart\nPress ESC to return to menu", score);
    sfText_setString(text, game_over_str);
    sfText_setCharacterSize(text, 40);
    sfText_setPosition(text, (sfVector2f) { WINDOW_WIDTH / 2 - 250, WINDOW_HEIGHT / 2 - 60 });
    sfText_setColor(text, sfBlack);
    sfRenderWindow_drawText(window, text, NULL);
}

void cleanup_render(Game* game) {
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        sfSprite_destroy(game->backgrounds[i]);
    }
    sfSprite_destroy(game->ground);
    sfText_destroy(game->score_text);
    sfFont_destroy(game->font);
    sfSprite_destroy(game->player->sprite);
    for (int i = 0; i < game->pipe_count; i++) {
        sfSprite_destroy(game->pipes[i].top_sprite);
        sfSprite_destroy(game->pipes[i].bottom_sprite);
    }
    sfMusic_destroy(game->background_music);
    sfSound_destroy(game->jump_sound);
    sfSound_destroy(game->crash_sound);
    sfSoundBuffer_destroy(game->jump_buffer);
    sfSoundBuffer_destroy(game->crash_buffer);
    free(game->player);
    free(game->pipes);
}