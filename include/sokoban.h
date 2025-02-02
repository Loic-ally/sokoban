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

    #define WINDOW_WIDTH 900
    #define WINDOW_HEIGHT 900
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
    char grid[MAX_HEIGHT][MAX_WIDTH];
    Position player;
    Position* boxes;
    Position* targets;
    int numBoxes;
} Level;

typedef struct {
    sfSprite* playerSprite;
    sfSprite* wallSprite;
    sfSprite* boxSprite;
    sfSprite* targetSprite;
    sfSprite* floorSprite;
} Assets;

typedef struct {
    char playerName[MAX_NAME_LENGTH];
    int score;
} Player;

int selectDifficulty(sfRenderWindow* window, sfFont* font);

#endif /* SOKOBAN_H */