#include "pipes.h"
#include <SFML/Graphics.h>
#include <stdlib.h>
#include <stdio.h>

void init_pipes(Pipe* pipes, int count, sfTexture* texture) {
    for (int i = 0; i < count; i++) {
        pipes[i].top_sprite = sfSprite_create();
        pipes[i].bottom_sprite = sfSprite_create();
        sfSprite_setTexture(pipes[i].top_sprite, texture, sfTrue);
        sfSprite_setTexture(pipes[i].bottom_sprite, texture, sfTrue);
        sfSprite_setScale(pipes[i].top_sprite, (sfVector2f) { 1.5625f, 3.846f });
        sfSprite_setScale(pipes[i].bottom_sprite, (sfVector2f) { 1.5625f, 3.846f });

        pipes[i].x_position = WINDOW_WIDTH + i * PIPE_SPACING;
        pipes[i].gap_y = (rand() % (380 - 220 + 1)) + 220;

        float pipe_height = sfTexture_getSize(texture).y * 3.846f;

        sfSprite_setPosition(pipes[i].top_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y - PIPE_GAP / 2.0f - pipe_height });
        sfSprite_setPosition(pipes[i].bottom_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y + PIPE_GAP / 2.0f });

        pipes[i].passed = sfFalse;
    }
}

void update_pipes(Pipe* pipes, int count, float delta_time, Player* player, int* score, float* pipe_speed) {
    float max_x = pipes[0].x_position;
    for (int i = 1; i < count; i++) {
        if (pipes[i].x_position > max_x) {
            max_x = pipes[i].x_position;
        }
    }

    for (int i = 0; i < count; i++) {
        pipes[i].x_position -= *pipe_speed * delta_time;

        if (pipes[i].x_position < -(float)sfTexture_getSize(sfSprite_getTexture(pipes[i].top_sprite)).x) {
            pipes[i].x_position = max_x + PIPE_SPACING;
          
            pipes[i].gap_y = (rand() % (380 - 220 + 1)) + 220;
            pipes[i].passed = sfFalse;
            max_x = pipes[i].x_position;
        }

        float pipe_height = sfTexture_getSize(sfSprite_getTexture(pipes[i].top_sprite)).y * 3.846f;

        sfSprite_setPosition(pipes[i].top_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y - PIPE_GAP / 2.0f - pipe_height });
        sfSprite_setPosition(pipes[i].bottom_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y + PIPE_GAP / 2.0f });

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
        pipes[i].gap_y = (rand() % (380 - 220 + 1)) + 220;
        pipes[i].passed = sfFalse;

        float pipe_height = sfTexture_getSize(sfSprite_getTexture(pipes[i].top_sprite)).y * 3.846f;

        sfSprite_setPosition(pipes[i].top_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y - PIPE_GAP / 2.0f - pipe_height });
        sfSprite_setPosition(pipes[i].bottom_sprite, (sfVector2f) { pipes[i].x_position, pipes[i].gap_y + PIPE_GAP / 2.0f });
    }
}

sfBool check_collisions(Player* player, Pipe* pipes, int count) {
    sfFloatRect player_bounds = sfSprite_getGlobalBounds(player->sprite);

    float player_scale = 2.5f;
    float player_reduction = 0.3f;
    player_bounds.width *= (1.0f - player_reduction);
    player_bounds.height *= (1.0f - player_reduction);
    player_bounds.left += (player_bounds.width * player_reduction) / 2.0f;
    player_bounds.top += (player_bounds.height * player_reduction) / 2.0f;

    for (int i = 0; i < count; i++) {
        sfFloatRect top_pipe_bounds = sfSprite_getGlobalBounds(pipes[i].top_sprite);
        sfFloatRect bottom_pipe_bounds = sfSprite_getGlobalBounds(pipes[i].bottom_sprite);

        float pipe_reduction = 0.1f;
        top_pipe_bounds.width *= (1.0f - pipe_reduction);
        bottom_pipe_bounds.width *= (1.0f - pipe_reduction);
        top_pipe_bounds.left += (top_pipe_bounds.width * pipe_reduction) / 2.0f;
        bottom_pipe_bounds.left += (bottom_pipe_bounds.width * pipe_reduction) / 2.0f;

        if (sfFloatRect_intersects(&player_bounds, &top_pipe_bounds, NULL) ||
            sfFloatRect_intersects(&player_bounds, &bottom_pipe_bounds, NULL)) {
            return sfTrue;
        }
    }

    if (player->position.y >= WINDOW_HEIGHT - GROUND_HEIGHT) {
        return sfTrue;
    }

    return sfFalse;
}