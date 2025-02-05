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
} Assets;

typedef struct {
    char playerName[MAX_NAME_LENGTH];
    int score;
    int difficulty;
} Player;

int selectDifficulty(sfRenderWindow* window, sfFont* font);
Assets loadAssets(int difficulty, sfRenderWindow* window);
void freeAssets(Assets assets);
void freeLevel(Level* level);
bool checkWin(Level* level);
Assets movePlayer(Level* level, int dx, int dy, Assets assets, int* animationDirection);
Level* generateLevel(int minBoxes, int maxBoxes, int numPokemons);
bool isMapSolvable(Level* level);
bool canReachTarget(Level* level, Position box, Position target);
void displayMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level, int* minBoxes, int* maxBoxes, Assets* assets, int* numPokemons, sfMusic* menuMusic);
int displayGameMenu(sfRenderWindow* window, Assets* assets, sfMusic* menuMusic);
void askPlayerName(sfRenderWindow* window, sfFont* font, Player* player);
void saveScore(Player player);
void loadScore(Player* player);
void renderLevel(sfRenderWindow* window, Level* level, Assets assets, int numPokemons, int animationDirection);
sfTexture* customCharacter(sfRenderWindow* window, Assets assets); // Add this line

#endif // SOKOBAN_H