#include "game.h"
#include "render.h"
#include "input.h"
#include "player.h"
#include "pipes.h"
#include <SFML/Graphics.h>
#include <stdio.h>

int main() {
    // Initialiser la fenêtre SFML
    sfVideoMode mode = { WINDOW_WIDTH, WINDOW_HEIGHT, 32 };
    sfRenderWindow* window = sfRenderWindow_create(mode, "Flappy Bird", sfClose, NULL);
    if (!window) return 1;
    sfRenderWindow_setFramerateLimit(window, 60);

    // Initialiser le jeu
    Game game;
    init_game(&game, window);

    // Créer un texte pour le menu et game over
    sfText* menu_text = sfText_create();
    sfText_setFont(menu_text, game.font);

    // Variables pour la boucle de jeu
    sfClock* clock = sfClock_create();
    sfBool jump = sfFalse;

    // Boucle principale
    while (sfRenderWindow_isOpen(window)) {
        // Calculer le temps écoulé
        float delta_time = sfTime_asSeconds(sfClock_restart(clock));

        // Gérer les entrées selon l'état
        switch (game.state) {
        case MENU:
            handle_menu_input(window, &game);
            break;
        case PLAYING:
            jump = sfFalse; // Réinitialiser le saut
            handle_input(window, &game, &jump);
            update_game(&game, delta_time);
            break;
        case GAME_OVER:
            handle_game_over_input(window, &game);
            break;
        }

        // Effacer l'écran
        sfRenderWindow_clear(window, sfBlack);

        // Dessiner les éléments
        draw_background(window, game.background);
        if (game.state == PLAYING || game.state == GAME_OVER) {
            draw_pipes(window, game.pipes, game.pipe_count);
            draw_player(window, game.player);
            draw_score(window, game.score_text, game.score);
        }
        draw_ground(window, game.ground);

        // Dessiner le menu ou game over
        if (game.state == MENU) {
            draw_menu(window, menu_text);
        }
        else if (game.state == GAME_OVER) {
            draw_game_over(window, menu_text, game.score);
        }

        // Afficher le rendu
        sfRenderWindow_display(window);
    }

    // Nettoyer les ressources
    sfText_destroy(menu_text);
    sfClock_destroy(clock);
    cleanup_render(&game);
    sfRenderWindow_destroy(window);

    return 0;
}