#pragma once
#include <SFML/Graphics.h>
#include <SFML/System.h>

// Constantes du jeu
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRAVITY 800.0f // Réduire la gravité pour une chute plus douce
#define JUMP_VELOCITY -300.0f // Augmenter la vitesse de saut
#define PIPE_SPEED 200.0f // pixels/s
#define PIPE_SPACING 300 // Distance entre tuyaux
#define PIPE_GAP 150 // Taille de l'ouverture entre tuyaux
#define GROUND_HEIGHT 60 // Hauteur du sol

// États du jeu
typedef enum {
    MENU,
    PLAYING,
    GAME_OVER
} GameState;

// Structure pour le joueur
typedef struct {
    sfSprite* sprite;
    sfVector2f position;
    float velocity;
} Player;

// Structure pour un tuyau
typedef struct {
    sfSprite* top_sprite;
    sfSprite* bottom_sprite;
    float x_position;
    int gap_y; // Position y du centre de l'ouverture
    sfBool passed; // Indique si le joueur a passé ce tuyau
} Pipe;

// Structure pour l'état global du jeu
typedef struct {
    GameState state;
    Player* player;
    Pipe* pipes;
    int pipe_count;
    int score;
    sfSprite* background;
    sfSprite* ground;
    sfFont* font;
    sfText* score_text;
} Game;

// Prototypes des fonctions (définies dans game.c)
void init_game(Game* game, sfRenderWindow* window);
void update_game(Game* game, float delta_time, sfBool jump);
void reset_game(Game* game);

