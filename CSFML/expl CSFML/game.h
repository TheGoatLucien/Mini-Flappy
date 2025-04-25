#pragma once
#include <SFML/Graphics.h>
#include <SFML/System.h>

// Constantes du jeu
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRAVITY 900.0f
#define JUMP_VELOCITY -300.0f
#define PIPE_SPEED 180.0f
#define PIPE_SPEED_INCREMENT 5.0f
#define PIPE_SPEED_MAX 400.0f
#define SCORE_SPEED_THRESHOLD 5
#define PIPE_SPACING 300
#define PIPE_GAP 170
#define GROUND_HEIGHT 60
#define MAX_SCORES 7

// États du jeu
typedef enum {
    MENU,
    PLAYING,
    GAME_OVER
} GameState;

// Sous-états pour le menu
typedef enum {
    MENU_BIRD_SELECTION,
    MENU_HIGH_SCORES
} MenuSubState;

// Structure pour le joueur
typedef struct {
    sfSprite* sprite;
    sfVector2f position;
    float velocity;
    int selected_bird;
    int anim_frame;
    float anim_timer;
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
    MenuSubState menu_substate; // Sous-état pour le menu
    Player* player;
    Pipe* pipes;
    int pipe_count;
    int score;
    int high_scores[MAX_SCORES]; // Tableau des meilleurs scores
    float pipe_speed;
    sfSprite* background;
    sfSprite* ground;
    sfFont* font;
    sfText* score_text;
} Game;

// Prototypes des fonctions (définies dans game.c)
void init_game(Game* game, sfRenderWindow* window);
void update_game(Game* game, float delta_time, sfBool jump);
void reset_game(Game* game);