#include "pipes.h"
#include <SFML/Graphics.h>
#include <stdlib.h>

void init_pipes(Pipe* pipes, int count, sfTexture* texture) {
    for (int i = 0; i < count; i++) {
        pipes[i].top_sprite = sfSprite_create();
        pipes[i].bottom_sprite = sfSprite_create();
        sfSprite_setTexture(pipes[i].top_sprite, texture, sfTrue);
        sfSprite_setTexture(pipes[i].bottom_sprite, texture, sfTrue);
        sfSprite_setScale(pipes[i].top_sprite, (sfVector2f) { 1.5625f, 3.846f }); // Échelle pour les tuyaux
        sfSprite_setScale(pipes[i].bottom_sprite, (sfVector2f) { 1.5625f, 3.846f });
        // Position initiale (tuyaux espacés à droite de l'écran)
        pipes[i].x_position = WINDOW_WIDTH + i * PIPE_SPACING;
        // Position aléatoire de l'ouverture
        pipes[i].gap_y = (rand() % (WINDOW_HEIGHT - GROUND_HEIGHT - PIPE_GAP - 200)) + 100;

        // Positionner les sprites
        sfSprite_setPosition(pipes[i].top_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y - PIPE_GAP / 2.0f - sfTexture_getSize(texture).y * 3.846f });
        sfSprite_setPosition(pipes[i].bottom_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y + PIPE_GAP / 2.0f });
        pipes[i].passed = sfFalse;
    }
}

void update_pipes(Pipe* pipes, int count, float delta_time, Player* player, int* score) {
    for (int i = 0; i < count; i++) {
        // Déplacer les tuyaux vers la gauche
        pipes[i].x_position -= PIPE_SPEED * delta_time;

        // Repositionner si le tuyau sort de l'écran
        if (pipes[i].x_position < -(int)sfTexture_getSize(sfSprite_getTexture(pipes[i].top_sprite)).x) {
            pipes[i].x_position += count * PIPE_SPACING;
            pipes[i].gap_y = (rand() % (WINDOW_HEIGHT - GROUND_HEIGHT - PIPE_GAP - 200)) + 100;
            pipes[i].passed = sfFalse;
        }

        // Mettre à jour les positions des sprites
        sfSprite_setPosition(pipes[i].top_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y - PIPE_GAP / 2.0f - sfTexture_getSize(sfSprite_getTexture(pipes[i].top_sprite)).y * 3.846f });
        sfSprite_setPosition(pipes[i].bottom_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y + PIPE_GAP / 2.0f });

        // Incrémenter le score si le joueur passe le tuyau
        if (!pipes[i].passed && pipes[i].x_position < player->position.x) {
            (*score)++;
            pipes[i].passed = sfTrue;
        }
    }
}

void draw_pipes(sfRenderWindow* window, Pipe* pipes, int count) {
    for (int i = 0; i < count; i++) {
        sfRenderWindow_drawSprite(window, pipes[i].top_sprite, NULL);
        sfRenderWindow_drawSprite(window, pipes[i].bottom_sprite, NULL);
    }
}

void reset_pipes(Pipe* pipes, int count) {
    for (int i = 0; i < count; i++) {
        pipes[i].x_position = WINDOW_WIDTH + i * PIPE_SPACING;
        pipes[i].gap_y = (rand() % (WINDOW_HEIGHT - GROUND_HEIGHT - PIPE_GAP - 200)) + 100;
        pipes[i].passed = sfFalse;
        sfSprite_setPosition(pipes[i].top_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y - PIPE_GAP / 2.0f - sfTexture_getSize(sfSprite_getTexture(pipes[i].top_sprite)).y });
        sfSprite_setPosition(pipes[i].bottom_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y + PIPE_GAP / 2.0f });
    }
}

sfBool check_collisions(Player* player, Pipe* pipes, int count) {
    sfFloatRect player_bounds = sfSprite_getGlobalBounds(player->sprite);

    for (int i = 0; i < count; i++) {
        sfFloatRect top_pipe_bounds = sfSprite_getGlobalBounds(pipes[i].top_sprite);
        sfFloatRect bottom_pipe_bounds = sfSprite_getGlobalBounds(pipes[i].bottom_sprite);

        // Vérifier les collisions avec les tuyaux
        if (sfFloatRect_intersects(&player_bounds, &top_pipe_bounds, NULL) ||
            sfFloatRect_intersects(&player_bounds, &bottom_pipe_bounds, NULL)) {
            return sfTrue;
        }
    }

    // Vérifier la collision avec le sol
    if (player->position.y >= WINDOW_HEIGHT - GROUND_HEIGHT) {
        return sfTrue;
    }

    return sfFalse;
}