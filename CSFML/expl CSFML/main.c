#include "game.h"
#include "render.h"
#include "input.h"
#include "player.h"
#include "pipes.h"
#include <SFML/Graphics.h>
#include <stdio.h>

int main() {
    sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "Flappy Bird", sfClose, NULL);
    if (!window) return 1;
    sfRenderWindow_setFramerateLimit(window, 60);

    Game game;
    init_game(&game, window);

    sfText* menu_text = sfText_create();
    sfText_setFont(menu_text, game.font);

    sfSprite* bird_sprite = sfSprite_create();
    sfTexture* bird_texture = sfTexture_createFromFile("../Ressources/Textures/ALLBird1.png", NULL);
    sfSprite_setTexture(bird_sprite, bird_texture, sfTrue);
    sfSprite_setScale(bird_sprite, (sfVector2f) { 2.5f, 2.5f });

    sfClock* clock = sfClock_create();
    sfBool jump = sfFalse;
    sfBool return_to_menu = sfFalse;
    int selected_bird = 0;

    while (sfRenderWindow_isOpen(window)) {
        float delta_time = sfTime_asSeconds(sfClock_restart(clock));

        switch (game.state) {
        case MENU:
            handle_menu_input(window, &game, &selected_bird, &game.menu_substate);
            break;
        case PLAYING:
            jump = sfFalse;
            handle_input(window, &game, &jump);
            update_game(&game, delta_time, jump);
            break;
        case GAME_OVER:
            return_to_menu = sfFalse;
            handle_game_over_input(window, &game, &return_to_menu);
            if (return_to_menu) {
                reset_game(&game);
                game.state = MENU;
                game.menu_substate = MENU_BIRD_SELECTION;
            }
            break;
        }

        sfRenderWindow_clear(window, sfBlack);

        draw_background(window, game.current_background, game.next_background, game.transition_timer);
        if (game.state == PLAYING || game.state == GAME_OVER) {
            draw_pipes(window, game.pipes, game.pipe_count);
            draw_player(window, game.player);
            draw_score(window, game.score_text, game.score);
        }
        draw_ground(window, game.ground);

        if (game.state == MENU) {
            draw_menu(window, menu_text, bird_sprite, selected_bird, game.menu_substate, game.high_scores);
        }
        else if (game.state == GAME_OVER) {
            draw_game_over(window, menu_text, game.score);
        }

        sfRenderWindow_display(window);
    }

    sfSprite_destroy(bird_sprite);
    sfTexture_destroy(bird_texture);
    sfText_destroy(menu_text);
    sfClock_destroy(clock);
    cleanup_render(&game);
    sfRenderWindow_destroy(window);

    return 0;
}