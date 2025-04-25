#include "player.h"
#include <SFML/Graphics.h>

void init_player(Player* player, sfTexture* texture) {
    player->sprite = sfSprite_create();
    sfSprite_setTexture(player->sprite, texture, sfTrue);
    sfSprite_setScale(player->sprite, (sfVector2f) { 2.5f, 2.5f });

    sfVector2u texture_size = sfTexture_getSize(texture);
    sfSprite_setOrigin(player->sprite, (sfVector2f) { texture_size.x / 8.0f, texture_size.y / 14.0f }); // Origine ajustée pour 16x15

    // Position initiale
    player->position = (sfVector2f){ WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 3.0f };
    sfSprite_setPosition(player->sprite, player->position);

    // Initialisation des paramètres
    player->velocity = 0.0f;
    player->selected_bird = 0; // Oiseau par défaut
    player->anim_frame = 0;
    player->anim_timer = 0.0f;

    // Définir la région de la texture pour l'oiseau sélectionné (frame 0)
    sfSprite_setTextureRect(player->sprite, (sfIntRect) { 0, 0, 16, 15 });
}

void update_player(Player* player, float delta_time, sfBool jump) {
    // Gérer le saut
    if (jump) {
        if (player->velocity > 0) {
            player->velocity = JUMP_VELOCITY;
        }
        else {
            player->velocity = JUMP_VELOCITY;
        }
    }

    // Appliquer la gravité
    player->velocity += GRAVITY * delta_time;
    player->position.y += player->velocity * delta_time;

    // Limiter la position
    if (player->position.y < 0) {
        player->position.y = 0;
        player->velocity = 0;
    }
    if (player->position.y > WINDOW_HEIGHT - GROUND_HEIGHT) {
        player->position.y = WINDOW_HEIGHT - GROUND_HEIGHT;
        player->velocity = 0;
    }

    // Mettre à jour la position du sprite
    sfSprite_setPosition(player->sprite, player->position);

    // Rotation pour l'effet visuel
    float angle = player->velocity * 0.05f;
    if (angle > 45.0f) angle = 45.0f;
    if (angle < -45.0f) angle = -45.0f;
    sfSprite_setRotation(player->sprite, angle);

    // Mettre à jour l'animation
    update_player_animation(player, delta_time);
}

void update_player_animation(Player* player, float delta_time) {
    player->anim_timer += delta_time;
    if (player->anim_timer >= 0.1f) { // Changer de frame toutes les 0.1 secondes
        player->anim_frame = (player->anim_frame + 1) % 4; // Boucle sur 3 frames (0, 1, 2)
        player->anim_timer = 0.0f;

        // Mettre à jour la région de la texture en fonction de l'oiseau et de la frame
        int bird_row = player->selected_bird * 16; // Chaque oiseau est sur une ligne (16 pixels de haut)
        int frame_col = player->anim_frame * 16; // Chaque frame est espacée de 16 pixels en largeur
        sfSprite_setTextureRect(player->sprite, (sfIntRect) { frame_col, bird_row, 16, 15 });
    }
}

void draw_player(sfRenderWindow* window, Player* player) {
    sfRenderWindow_drawSprite(window, player->sprite, NULL);
}

void reset_player(Player* player) {
    player->position = (sfVector2f){ WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 3.0f };
    player->velocity = 0.0f;
    sfSprite_setPosition(player->sprite, player->position);
    sfSprite_setRotation(player->sprite, 0.0f);
    player->anim_frame = 0;
    player->anim_timer = 0.0f;
    // Réinitialiser la région de la texture
    sfSprite_setTextureRect(player->sprite, (sfIntRect) { 0, player->selected_bird * 16, 16, 15 });
}