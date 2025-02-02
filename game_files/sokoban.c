/*
** EPITECH PROJECT, 2024
** test
** File description:
** sokoban.c
*/

#include "../include/sokoban.h"

bool isValid(int x, int y)
{
    return (unsigned)x < MAX_WIDTH && (unsigned)y < MAX_HEIGHT;
}

Position getRandomEmptyPosition(Level* level)
{
    Position pos;

    do {
        pos.x = rand() % (MAX_WIDTH - 2) + 1;
        pos.y = rand() % (MAX_HEIGHT - 2) + 1;
    } while (level->grid[pos.y][pos.x] != ' ');
    return pos;
}

bool canReachTarget(Level* level, Position box, Position target)
{
    bool visited[MAX_HEIGHT][MAX_WIDTH] = {false};
    Position queue[MAX_WIDTH * MAX_HEIGHT];
    int front = 0, rear = 0;
    const int dx[] = {0, 1, 0, -1};
    const int dy[] = {-1, 0, 1, 0};
    Position current;
    int newY;
    int newX;
    int pushX;
    int pushY;
    
    queue[rear++] = box;
    visited[box.y][box.x] = true;
    while (front < rear) {
        current = queue[front++];
        if (current.x == target.x && current.y == target.y)
            return true;
        for (int i = 0; i < 4; i++) {
            newX = current.x + dx[i];
            newY = current.y + dy[i];
            if (isValid(newX, newY) && !visited[newY][newX] && 
                level->grid[newY][newX] != '#') {
                pushX = current.x - dx[i];
                pushY = current.y - dy[i];
                if (isValid(pushX, pushY) && level->grid[pushY][pushX] != '#') {
                    queue[rear].x = newX;
                    queue[rear].y = newY;
                    rear++;
                    visited[newY][newX] = true;
                }
            }
        }
    }
    return false;
}

bool isMapSolvable(Level* level)
{
    //Ici va faloir surement dmd a une ia comment faire parce que aucune idée
    for (int i = 0; i < level->numBoxes; i++) {
        if (!canReachTarget(level, level->boxes[i], level->targets[i]))
            return false;
    }
    return true;
}

Level* generateLevel(int minBoxes, int maxBoxes)
{
    Level* level;
    bool solvable = false;

    while (!solvable) {
        level = (Level*)malloc(sizeof(Level));
        level->numBoxes = minBoxes + rand() % (maxBoxes - minBoxes + 1);
        level->boxes = (Position*)malloc(level->numBoxes * sizeof(Position));
        level->targets = (Position*)malloc(level->numBoxes * sizeof(Position));

        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int x = 0; x < MAX_WIDTH; x++) {
                if (x == 0 || x == MAX_WIDTH - 1 || y == 0 || y == MAX_HEIGHT - 1)
                    level->grid[y][x] = '#';
                else
                    level->grid[y][x] = ' ';
            }
        }
        for (int y = 1; y < MAX_HEIGHT - 1; y++) {
            for (int x = 1; x < MAX_WIDTH - 1; x++) {
                if (rand() % 100 < 30) {
                    level->grid[y][x] = '#';
                }
            }
        }
        level->player = getRandomEmptyPosition(level);
        level->grid[level->player.y][level->player.x] = 'P';
        for (int i = 0; i < level->numBoxes; i++) {
            do {
                level->boxes[i] = getRandomEmptyPosition(level);
            } while (level->grid[level->boxes[i].y][level->boxes[i].x] == 'T');
            level->grid[level->boxes[i].y][level->boxes[i].x] = 'B';

            do {
                level->targets[i] = getRandomEmptyPosition(level);
            } while (level->grid[level->targets[i].y][level->targets[i].x] == 'B');
            level->grid[level->targets[i].y][level->targets[i].x] = 'T';
        }
        solvable = isMapSolvable(level);
        if (!solvable) {
            freeLevel(level);
        }
    }
    return level;
}

void renderLevel(sfRenderWindow* window, Level* level, Assets assets)
{
    float offsetX = (WINDOW_WIDTH - MAX_WIDTH * TILE_SIZE) / 2;
    float offsetY = (WINDOW_HEIGHT - MAX_HEIGHT * TILE_SIZE) / 2;
    sfVector2f playerPos;
    sfVector2f pos;

    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            pos = (sfVector2f){x * TILE_SIZE + offsetX, y * TILE_SIZE + offsetY};
            
            sfSprite_setPosition(assets.floorSprite, pos);
            sfRenderWindow_drawSprite(window, assets.floorSprite, NULL);
            
            switch (level->grid[y][x]) {
                case '#':
                    sfSprite_setPosition(assets.wallSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.wallSprite, NULL);
                    break;
                case 'B':
                    sfSprite_setPosition(assets.boxSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.boxSprite, NULL);
                    break;
                case 'T':
                    sfSprite_setPosition(assets.targetSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.targetSprite, NULL);
                    break;
            }
        }
    }

    playerPos = (sfVector2f){level->player.x * TILE_SIZE + offsetX, level->player.y * TILE_SIZE + offsetY};
    sfSprite_setPosition(assets.playerSprite, playerPos);
    sfRenderWindow_drawSprite(window, assets.playerSprite, NULL);
}

bool movePlayer(Level* level, int dx, int dy)
{
    int newX = level->player.x + dx;
    int newY = level->player.y + dy;
    int pushX;
    int pushY;
    bool isBox = false;
    int boxIndex = -1;
    bool isOnTarget = false;
    
    if (!isValid(newX, newY) || level->grid[newY][newX] == '#' || level->grid[newY][newX] == 'T')
        return false;
    for (int i = 0; i < level->numBoxes; i++) {
        if (level->boxes[i].x == newX && level->boxes[i].y == newY) {
            isBox = true;
            boxIndex = i;
            break;
        }
    }

    if (isBox) {
        pushX = newX + dx;
        pushY = newY + dy;

        if (!isValid(pushX, pushY) || level->grid[pushY][pushX] == '#')
            return false;

        for (int i = 0; i < level->numBoxes; i++) {
            if (level->boxes[i].x == pushX && level->boxes[i].y == pushY)
                return false;
        }

        isOnTarget = false;
        for (int i = 0; i < level->numBoxes; i++) {
            if (level->targets[i].x == pushX && level->targets[i].y == pushY) {
                isOnTarget = true;
                break;
            }
        }
        
        level->grid[level->boxes[boxIndex].y][level->boxes[boxIndex].x] = ' ';
        level->boxes[boxIndex].x = pushX;
        level->boxes[boxIndex].y = pushY;

        if (isOnTarget) {
            level->grid[pushY][pushX] = ' ';
            for (int i = boxIndex; i < level->numBoxes - 1; i++) {
                level->boxes[i] = level->boxes[i + 1];
            }
            level->numBoxes--;
        } else {
            level->grid[pushY][pushX] = 'B';
        }
    }

    level->grid[level->player.y][level->player.x] = ' ';
    level->player.x = newX;
    level->player.y = newY;
    level->grid[newY][newX] = 'P';
    
    return true;
}

bool checkWin(Level* level)
{
    bool* targetUsed = (bool*)calloc(level->numBoxes, sizeof(bool));
    bool boxOnTarget = false;

    for (int i = 0; i < level->numBoxes; i++) {
        boxOnTarget = false;
        for (int j = 0; j < level->numBoxes; j++) {
            if (!targetUsed[j] && 
                level->boxes[i].x == level->targets[j].x && 
                level->boxes[i].y == level->targets[j].y) {
                targetUsed[j] = true;
                boxOnTarget = true;
                break;
            }
        }
        if (!boxOnTarget) {
            free(targetUsed);
            return false;
        }
    }

    free(targetUsed);
    return true;
}

void freeLevel(Level* level)
{
    free(level->boxes);
    free(level->targets);
    free(level);
}

void freeAssets(Assets assets)
{
    sfSprite_destroy(assets.playerSprite);
    sfSprite_destroy(assets.wallSprite);
    sfSprite_destroy(assets.boxSprite);
    sfSprite_destroy(assets.targetSprite);
    sfSprite_destroy(assets.floorSprite);
}
