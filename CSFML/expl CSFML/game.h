#pragma once
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Audio.h>

// Constantes du jeu
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define GRAVITY 900.0f
#define JUMP_VELOCITY -300.0f // Vitesse de saut
#define PIPE_SPEED 180.0f // Vitesse initiale des tuyaux
#define PIPE_SPEED_INCREMENT 5.0f // Incrément de vitesse par score
#define PIPE_SPEED_MAX 1000.0f // Vitesse maximale des tuyaux
#define SCORE_SPEED_THRESHOLD 5 // Seuil de score pour augmenter la vitesse des tuyaux
#define PIPE_SPACING 300 // Espacement entre les tuyaux
#define PIPE_GAP 170 // Espace entre les tuyaux
#define GROUND_HEIGHT 60 // Hauteur du sol
#define MAX_SCORES 7 // Nombre de scores à sauvegarder
#define NUM_BACKGROUNDS 9 // Nombre d'images de fond
#define SCORE_PER_BACKGROUND 10 // Score pour changer d'image de fond
#define TRANSITION_DURATION 1.0f // Durée de la transition entre les images de fond

// États du jeu
typedef enum {
    MENU,
    PLAYING,
    GAME_OVER
} GameState; 

// Sous-états pour le menu
typedef enum {
	MENU_BIRD_SELECTION, // Sélection de l'oiseau
	MENU_HIGH_SCORES // Affichage des scores
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
	sfSprite* top_sprite; // Sprite pour le tuyau supérieur
	sfSprite* bottom_sprite; // Sprites pour les tuyaux supérieur et inférieur
	float x_position; // Position horizontale du tuyau
	int gap_y; // Position de l'espace entre les tuyaux
	sfBool passed; // Indique si le joueur a passé le tuyau
} Pipe;

// Structure pour l'état global du jeu
typedef struct {
    GameState state;
	MenuSubState menu_substate; // Sous-état du menu
    Player* player;
    Pipe* pipes;
    int pipe_count;
    int score;
    int high_scores[MAX_SCORES];
    float pipe_speed;
    sfSprite* backgrounds[NUM_BACKGROUNDS];
    int current_background_index;
    int target_background_index; // Index cible basé sur le score
	float transition_timer; // Timer pour la transition entre les images de fond
	sfSprite* current_background; // Image de fond actuelle
    sfSprite* next_background;
    sfMusic* background_music;
    sfSound* jump_sound;
    sfSound* crash_sound;
    sfSoundBuffer* jump_buffer;
    sfSoundBuffer* crash_buffer;
    sfSprite* ground;
    sfFont* font;
    sfText* score_text;
} Game;

// Prototypes des fonctions (définies dans game.c)
void init_game(Game* game, sfRenderWindow* window);
void update_game(Game* game, float delta_time, sfBool jump);
void reset_game(Game* game);