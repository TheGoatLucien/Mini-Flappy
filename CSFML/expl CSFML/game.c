#include "game.h"
#include "player.h"
#include "pipes.h"
#include "render.h"
#include <stdlib.h>

void init_game(Game* game, sfRenderWindow* window) {
    // Allouer la mémoire pour le joueur
    game->player = (Player*)malloc(sizeof(Player));
    if (!game->player) exit(1);

    // Charger les textures
    sfTexture* player_texture = sfTexture_createFromFile("../Ressources/Textures/Bird.png", NULL);
    sfTexture* pipe_texture = sfTexture_createFromFile("../Ressources/Textures/Pipe.png", NULL);
    sfTexture* bg_texture = sfTexture_createFromFile("../Ressources/Textures/Background5.png", NULL);
    sfTexture* ground_texture = sfTexture_createFromFile("../Ressources/Textures/ground.png", NULL);
	//scale les textures
    
	


    // Initialiser le joueur
    init_player(game->player, player_texture);

    // Initialiser les tuyaux (3 tuyaux pour commencer)
    game->pipe_count = 3;
    game->pipes = (Pipe*)malloc(sizeof(Pipe) * game->pipe_count);
    if (!game->pipes) exit(1);
    init_pipes(game->pipes, game->pipe_count, pipe_texture);

    // Initialiser les sprites de fond et de sol
    game->background = sfSprite_create();
    sfSprite_setTexture(game->background, bg_texture, sfTrue);
    sfSprite_setScale(game->background, (sfVector2f) { 3.125f, 2.34375f }); // Échelle pour le fond

    game->ground = sfSprite_create();
    sfSprite_setTexture(game->ground, ground_texture, sfTrue);
    sfSprite_setScale(game->ground, (sfVector2f) { 12.5f, 1.935f }); // Échelle pour le sol
    sfSprite_setPosition(game->ground, (sfVector2f) { 0, WINDOW_HEIGHT - GROUND_HEIGHT });

    // Initialiser la police et le texte du score
    game->font = sfFont_createFromFile("../Ressources/Fonts/Bestime.ttf");
    game->score_text = sfText_create();
    sfText_setFont(game->score_text, game->font);
    sfText_setCharacterSize(game->score_text, 40);
    sfText_setPosition(game->score_text, (sfVector2f) { WINDOW_WIDTH / 2, 50 });
    sfText_setColor(game->score_text, sfBlack);

    // Initialiser l'état du jeu
    game->state = MENU;
    game->score = 0;
}

void update_game(Game* game, float delta_time, sfBool jump) {
    if (game->state != PLAYING) return;

    // Mettre à jour le joueur (saut géré par input.c)
 
    update_player(game->player, delta_time, jump);

    // Mettre à jour les tuyaux et le score
    update_pipes(game->pipes, game->pipe_count, delta_time, game->player, &game->score);

    // Vérifier les collisions
    if (check_collisions(game->player, game->pipes, game->pipe_count)) {
        game->state = GAME_OVER;
    }

    // Mettre à jour le texte du score
    char score_str[16];
    snprintf(score_str, sizeof(score_str), "%d", game->score);
    sfText_setString(game->score_text, score_str);
}

void reset_game(Game* game) {
    // Réinitialiser le joueur
    reset_player(game->player);

    // Réinitialiser les tuyaux
    reset_pipes(game->pipes, game->pipe_count);

    // Réinitialiser le score et l'état
    game->score = 0;
    game->state = PLAYING;
}