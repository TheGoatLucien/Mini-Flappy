#include "game.h"
#include "player.h"
#include "pipes.h"
#include "render.h"
#include "score.h"
#include <stdlib.h>

void init_game(Game* game, sfRenderWindow* window) {
    game->player = (Player*)malloc(sizeof(Player));
    if (!game->player) exit(1);

    sfTexture* player_texture = sfTexture_createFromFile("../Ressources/Textures/ALLBird1.png", NULL);
    sfTexture* pipe_texture = sfTexture_createFromFile("../Ressources/Textures/Pipe.png", NULL);
    sfTexture* bg_texture = sfTexture_createFromFile("../Ressources/Textures/Background5.png", NULL);
    sfTexture* ground_texture = sfTexture_createFromFile("../Ressources/Textures/ground.png", NULL);

    init_player(game->player, player_texture);

    game->pipe_count = 3;
    game->pipes = (Pipe*)malloc(sizeof(Pipe) * game->pipe_count);
    if (!game->pipes) exit(1);
    init_pipes(game->pipes, game->pipe_count, pipe_texture);

    game->background = sfSprite_create();
    sfSprite_setTexture(game->background, bg_texture, sfTrue);
    sfSprite_setScale(game->background, (sfVector2f) { 3.125f, 2.34375f });

    game->ground = sfSprite_create();
    sfSprite_setTexture(game->ground, ground_texture, sfTrue);
    sfSprite_setScale(game->ground, (sfVector2f) { 12.5f, 1.935f });
    sfSprite_setPosition(game->ground, (sfVector2f) { 0, WINDOW_HEIGHT - GROUND_HEIGHT });

    game->font = sfFont_createFromFile("../Ressources/Fonts/Bestime.ttf");
    game->score_text = sfText_create();
    sfText_setFont(game->score_text, game->font);
    sfText_setCharacterSize(game->score_text, 40);
    sfText_setPosition(game->score_text, (sfVector2f) { WINDOW_WIDTH / 2, 50 });
    sfText_setColor(game->score_text, sfBlack);

    // Charger les meilleurs scores
    load_high_scores(game->high_scores);

    game->state = MENU;
    game->menu_substate = MENU_BIRD_SELECTION;
    game->score = 0;
    game->pipe_speed = PIPE_SPEED;
}

void update_game(Game* game, float delta_time, sfBool jump) {
    if (game->state != PLAYING) return;

    update_player(game->player, delta_time, jump);

    game->pipe_speed = PIPE_SPEED + (game->score / SCORE_SPEED_THRESHOLD) * PIPE_SPEED_INCREMENT;
    if (game->pipe_speed > PIPE_SPEED_MAX) {
        game->pipe_speed = PIPE_SPEED_MAX;
    }

    update_pipes(game->pipes, game->pipe_count, delta_time, game->player, &game->score, &game->pipe_speed);

    if (check_collisions(game->player, game->pipes, game->pipe_count)) {
        // Mettre à jour les meilleurs scores avant de passer à GAME_OVER
        update_high_scores(game->high_scores, game->score);
        game->state = GAME_OVER;
    }

    char score_str[16];
    snprintf(score_str, sizeof(score_str), "%d", game->score);
    sfText_setString(game->score_text, score_str);
}

void reset_game(Game* game) {
    reset_player(game->player);
    reset_pipes(game->pipes, game->pipe_count);
    game->score = 0;
    game->pipe_speed = PIPE_SPEED;
    game->state = PLAYING;
}