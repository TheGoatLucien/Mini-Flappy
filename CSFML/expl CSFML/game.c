#include "game.h"
#include "player.h"
#include "pipes.h"
#include "render.h"
#include "score.h"
#include <stdlib.h>
#include <stdio.h>

void init_game(Game* game, sfRenderWindow* window) {
    game->player = (Player*)malloc(sizeof(Player));
    if (!game->player) exit(1);

    sfTexture* player_texture = sfTexture_createFromFile("../Ressources/Textures/ALLBird1.png", NULL);
    sfTexture* pipe_texture = sfTexture_createFromFile("../Ressources/Textures/Pipe.png", NULL);
    sfTexture* ground_texture = sfTexture_createFromFile("../Ressources/Textures/ground.png", NULL);

    // Charger les 9 backgrounds
    char bg_path[64];
    for (int i = 0; i < NUM_BACKGROUNDS; i++) {
        snprintf(bg_path, sizeof(bg_path), "../Ressources/Textures/Background%d.png", i + 1);
        sfTexture* bg_texture = sfTexture_createFromFile(bg_path, NULL);
        game->backgrounds[i] = sfSprite_create();
        sfSprite_setTexture(game->backgrounds[i], bg_texture, sfTrue);
        sfSprite_setScale(game->backgrounds[i], (sfVector2f) { 3.125f, 2.34375f });
    }

    // Initialiser les sprites pour la transition
    game->current_background = game->backgrounds[0];
    game->next_background = game->backgrounds[1];
    game->current_background_index = 0;
    game->target_background_index = 0;
    game->transition_timer = 0.0f;

    // Charger les sons
    game->background_music = sfMusic_createFromFile("../Ressources/Sounds/background_music.wav");
    sfMusic_setLoop(game->background_music, sfTrue);
    sfMusic_setVolume(game->background_music, 50.0f);
    sfMusic_play(game->background_music);

    game->jump_buffer = sfSoundBuffer_createFromFile("../Ressources/Sounds/jump.wav");
    game->jump_sound = sfSound_create();
    sfSound_setBuffer(game->jump_sound, game->jump_buffer);
    sfSound_setVolume(game->jump_sound, 80.0f);

    game->crash_buffer = sfSoundBuffer_createFromFile("../Ressources/Sounds/crash.wav");
    game->crash_sound = sfSound_create();
    sfSound_setBuffer(game->crash_sound, game->crash_buffer);
    sfSound_setVolume(game->crash_sound, 80.0f);

    init_player(game->player, player_texture);

    game->pipe_count = 3;
    game->pipes = (Pipe*)malloc(sizeof(Pipe) * game->pipe_count);
    if (!game->pipes) exit(1);
    init_pipes(game->pipes, game->pipe_count, pipe_texture);

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

    load_high_scores(game->high_scores);

    game->state = MENU;
    game->menu_substate = MENU_BIRD_SELECTION;
    game->score = 0;
    game->pipe_speed = PIPE_SPEED;
}

void update_game(Game* game, float delta_time, sfBool jump) {
    // Calculer l'index cible du background en fonction du score
    game->target_background_index = (game->score / SCORE_PER_BACKGROUND) % NUM_BACKGROUNDS;

    // Si une transition est en cours, mettre à jour le timer
    if (game->transition_timer > 0.0f && game->transition_timer < TRANSITION_DURATION) {
        game->transition_timer += delta_time;
        if (game->transition_timer >= TRANSITION_DURATION) {
            game->transition_timer = 0.0f;
            // À la fin de la transition, l'image cible devient l'image actuelle
            game->current_background_index = game->target_background_index;
            game->current_background = game->backgrounds[game->current_background_index];
            // Préparer la prochaine transition en définissant l'image suivante
            game->next_background = game->backgrounds[(game->current_background_index + 1) % NUM_BACKGROUNDS];
        }
    }

    // Si aucune transition n'est en cours, vérifier si on doit en déclencher une
    if (game->transition_timer == 0.0f && game->target_background_index != game->current_background_index) {
        game->transition_timer = 0.001f; // Déclencher la transition (éviter 0.0f pour indiquer qu'une transition est en cours)
        game->current_background = game->backgrounds[game->current_background_index];
        game->next_background = game->backgrounds[game->target_background_index];
    }

    if (game->state != PLAYING) {
        return;
    }

    update_player(game->player, delta_time, jump);

    game->pipe_speed = PIPE_SPEED + (game->score / SCORE_SPEED_THRESHOLD) * PIPE_SPEED_INCREMENT;
	//printf("Pipe speed: %f\n", game->pipe_speed); // Debug
    if (game->pipe_speed > PIPE_SPEED_MAX) {
        game->pipe_speed = PIPE_SPEED_MAX;
    }

    update_pipes(game->pipes, game->pipe_count, delta_time, game->player, &game->score, &game->pipe_speed);

    if (check_collisions(game->player, game->pipes, game->pipe_count)) {
        sfSound_play(game->crash_sound);
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
    game->current_background_index = 0;
    game->target_background_index = 0;
    game->transition_timer = 0.0f;
    game->current_background = game->backgrounds[0];
    game->next_background = game->backgrounds[1];
    game->state = PLAYING;
}