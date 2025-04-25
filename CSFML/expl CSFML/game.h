#pragma once
#include <SFML/Graphics.h>
#include <SFML/System.h>

// Constantes du jeu
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRAVITY 900.0f
#define JUMP_VELOCITY -300.0f
#define PIPE_SPEED 180.0f // Vitesse initiale des tuyaux
#define PIPE_SPEED_INCREMENT 5.0f // Augmentation de vitesse par palier
#define PIPE_SPEED_MAX 400.0f // Vitesse maximale
#define SCORE_SPEED_THRESHOLD 5 // Augmenter la vitesse tous les 5 points
#define PIPE_SPACING 300
#define PIPE_GAP 170
#define GROUND_HEIGHT 60

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
    int selected_bird; // Oiseau sélectionné (0 à 6)
    int anim_frame; // Frame d'animation actuelle (0 à 2)
    float anim_timer; // Timer pour l'animation
} Player;

// Structure pour un tuyau
typedef struct {
    sfSprite* top_sprite;
    sfSprite* bottom_sprite;
    float x_position;
    int gap_y;
    sfBool passed;
} Pipe;

// Structure pour l'état global du jeu
typedef struct {
    GameState state;
    Player* player;
    Pipe* pipes;
    int pipe_count;
    int score;
    float pipe_speed; // Vitesse dynamique des tuyaux
    sfSprite* background;
    sfSprite* ground;
    sfFont* font;
    sfText* score_text;
} Game;

// Prototypes des fonctions (définies dans game.c)
void init_game(Game* game, sfRenderWindow* window);
void update_game(Game* game, float delta_time, sfBool jump);
void reset_game(Game* game);