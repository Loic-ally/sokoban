/*
** EPITECH PROJECT, 2024
** test
** File description:
** sokoban.h
*/

#ifndef SOKOBAN_H
    #define SOKOBAN_H
    #include <SFML/Graphics.h>
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
    #define MAX_NAME_LENGTH 50
    #define MAX_STATES 1000000

typedef struct {
    int x, y;
} Position;

typedef struct {
    char grid[MAX_HEIGHT + 1][MAX_WIDTH + 1];
    Position player;
    Position* boxes;
    Position* targets;
    int numBoxes;
} Level;

typedef struct {
    sfSprite* playerSprite;
    sfSprite* backgroundSprite;
    sfSprite* boxSprite;
    sfSprite* targetSprite;
    sfSprite* floorSprite;
    sfSprite* wallSprite;
} Assets;

typedef struct {
    char playerName[MAX_NAME_LENGTH];
    int score;
    int difficulty;
} Player;

int selectDifficulty(sfRenderWindow* window, sfFont* font);
Assets loadAssets(int difficulty);
void freeAssets(Assets assets);
void freeLevel(Level* level);
bool checkWin(Level* level);
bool movePlayer(Level* level, int dx, int dy);
void renderLevel(sfRenderWindow* window, Level* level, Assets assets);
Level* generateLevel(int minBoxes, int maxBoxes);
bool isMapSolvable(Level* level);
bool canReachTarget(Level* level, Position box, Position target);
Position getRandomEmptyPosition(Level* level);
bool isValid(int x, int y);
void askPlayerName(sfRenderWindow* window, sfFont* font, Player* player);
void displayMenu(sfRenderWindow* window, sfFont* font, Player* player, Level **level, int minboxes, int maxboxes, Assets* assets);
void saveScore(Player player);
int getNumBoxesForDifficulty(int difficulty);
void loadScore(Player* player);

#endif /* SOKOBAN_H */