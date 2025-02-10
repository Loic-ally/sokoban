/*
** EPITECH PROJECT, 2024
** test
** File description:
** sokoban.h
*/

#ifndef SOKOBAN_H
#define SOKOBAN_H

#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <math.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define TILE_SIZE 50
#define SPRITE_SIZE 50
#define MAX_WIDTH 18
#define MAX_HEIGHT 18
#define MIN_BOXES 2
#define MAX_BOXES 10
#define MAX_NAME_LENGTH 11
#define MAX_STATES 1000000

typedef struct {
    int x, y;
} Position;

typedef struct {
    char grid[MAX_HEIGHT + 1][MAX_WIDTH + 1];
    Position player;
    Position* boxes;
    Position* targets;
    Position* pokemons;
    int numBoxes;
    int wallSpriteIndices[MAX_HEIGHT][MAX_WIDTH];
    int difficulty;
} Level;

typedef struct {
    sfSprite* playerSprite;
    sfSprite* backgroundSprite;
    sfSprite* boxSprite;
    sfSprite* targetSprite;
    sfSprite* floorSprite;
    sfSprite* wallSprite;
    sfSprite* pokemonSprites[6];
    sfTexture* pokemonTextures[6];
    sfTexture* wallTexture;
    sfMusic* levelMusic;
    sfSound* rockSound;
    sfSoundBuffer* rockSoundBuffer;
    sfSprite* splashSprite;
    sfTexture* splashTexture;
} Assets;

typedef struct {
    char playerName[MAX_NAME_LENGTH];
    int score;
    int difficulty;
} Player;

typedef struct {
    bool showGridLines;
    bool musicEnabled;
    int musicVolume;
    bool soundEffectsEnabled;
    int soundEffectsVolume;
    bool showMoveCounter;
    bool showTimer;
    bool showFps;
} GameSettings;

GameSettings *init_settings(void);
int selectDifficulty(sfRenderWindow* window, sfFont* font);
Assets loadAssets(int difficulty, sfRenderWindow* window);
void freeAssets(Assets assets);
void freeLevel(Level* level);
bool checkWin(Level* level);
Assets movePlayer(Level* level, int dx, int dy, Assets assets, int* animationDirection, int* moveCounter, GameSettings* setting, sfRenderWindow *window);
Level* generateLevel(int minBoxes, int maxBoxes, int numPokemons, int difficulty);
bool isMapSolvable(Level* level);
bool canReachTarget(Level* level, Position box, Position target);
void displayPauseMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level, int* minBoxes, int* maxBoxes, Assets* assets, int* numPokemons, sfMusic* menuMusic, GameSettings *setting);
void displayWinMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level, int* minBoxes, int* maxBoxes, Assets* assets, int* numPokemons, sfMusic* menuMusic);
int displayGameMenu(sfRenderWindow *window, Assets *assets, sfMusic* menuMusic, GameSettings* settings, sfMusic* levelMusic);
int askPlayerName(sfRenderWindow* window, sfFont* font, Player* player);
void saveScore(Player player);
void loadScore(Player* player);
int settings(sfRenderWindow* window, GameSettings* game_set, sfMusic* menuMusic, sfMusic* levelMusic);
void renderLevel(sfRenderWindow* window, Level* level, Assets assets, int numPokemons, int animationDirection, GameSettings* settings, sfFont* font, int moveCounter, sfClock* gameClock);
sfTexture* customCharacter(sfRenderWindow* window, Assets assets);
void apply_sound_settings(GameSettings* game_set, sfMusic* menuMusic, sfMusic* levelMusic);

#endif // SOKOBAN_H