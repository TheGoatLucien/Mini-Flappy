#include "player.h"
#include <SFML/Graphics.h>

void init_player(Player* player, sfTexture* texture) {
    // Initialiser le sprite du joueur
    player->sprite = sfSprite_create();
    sfSprite_setTexture(player->sprite, texture, sfTrue);
    sfSprite_setScale(player->sprite, (sfVector2f) { 2.5f, 2.5f }); // Échelle pour l'oiseau

    // Centrer l'origine du sprite pour une rotation fluide (optionnel)
    sfVector2u texture_size = sfTexture_getSize(texture);
    sfSprite_setOrigin(player->sprite, (sfVector2f) { texture_size.x / 2.0f, texture_size.y / 2.0f });

    // Position initiale (gauche de l'écran, milieu vertical)
    player->position = (sfVector2f){ WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 3.0f };
    sfSprite_setPosition(player->sprite, player->position);

    // Vitesse initiale
    player->velocity = 0.0f;
}

void update_player(Player* player, float delta_time, sfBool jump) {
    // Appliquer un saut si demandé
    if (jump) {
        if (player->velocity > 0) { // Si l'oiseau tombe, donner un boost plus fort
            player->velocity = JUMP_VELOCITY;
        }
        else {
            player->velocity = JUMP_VELOCITY; // Sinon, saut normal
        }
    }

    // Appliquer la gravité
    player->velocity += GRAVITY * delta_time;
    player->position.y += player->velocity * delta_time;

    // Limiter la position pour éviter de sortir de l'écran
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

    // Rotation simple pour l'effet visuel (en fonction de la vitesse)
    float angle = player->velocity * 0.05f; // Ajuster l'angle selon la vitesse
    if (angle > 45.0f) angle = 45.0f;
    if (angle < -45.0f) angle = -45.0f;
    sfSprite_setRotation(player->sprite, angle);
}

void draw_player(sfRenderWindow* window, Player* player) {
    sfRenderWindow_drawSprite(window, player->sprite, NULL);
}

void reset_player(Player* player) {
    // Réinitialiser la position et la vitesse
    player->position = (sfVector2f){ WINDOW_WIDTH / 4.0f, WINDOW_HEIGHT / 3.0f };
    player->velocity = 0.0f;
    sfSprite_setPosition(player->sprite, player->position);
    sfSprite_setRotation(player->sprite, 0.0f);
}