/*
** EPITECH PROJECT, 2024
** test
** File description:
** sokoban.c
*/

#include "../include/sokoban.h"

bool isValid(int x, int y)
{
    //demander a une ia parce que je suis pas jesus
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

Position getRandomEmptyPositionForPokemon()
{
    Position pos;
    int area = rand() % 4;

    switch (area) {
        case 0:
            pos.x = 
            pos.y = rand() % ((WINDOW_HEIGHT - 900) / 2);
            break;
        case 1:
            pos.x = rand() % WINDOW_WIDTH;
            pos.y = WINDOW_HEIGHT - ((WINDOW_HEIGHT - 900) / 2) + rand() % ((WINDOW_HEIGHT - 900) / 2);
            break;
        case 2:
            pos.x = rand() % ((WINDOW_WIDTH - 900) / 2);
            pos.y = rand() % WINDOW_HEIGHT;
            break;
        case 3:
            pos.x = WINDOW_WIDTH - ((WINDOW_WIDTH - 900) / 2) + rand() % ((WINDOW_WIDTH - 900) / 2);
            pos.y = rand() % WINDOW_HEIGHT;
            break;
    }

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
    for (int i = 0; i < level->numBoxes; i++) {
        if (!canReachTarget(level, level->boxes[i], level->targets[i]))
            return false;
    }
    return true;
}

Level* generateLevel(int minBoxes, int maxBoxes, int numPokemons)
{
    Level* level;
    bool solvable = false;

    while (!solvable) {
        level = (Level*)malloc(sizeof(Level));
        if (!level) {
            printf("Failed to allocate memory for level\n");
            return NULL;
        }
        level->numBoxes = minBoxes + rand() % (maxBoxes - minBoxes + 1);
        level->boxes = (Position*)malloc(level->numBoxes * sizeof(Position));
        level->targets = (Position*)malloc(level->numBoxes * sizeof(Position));
        level->pokemons = (Position*)malloc(numPokemons * sizeof(Position));
        if (!level->boxes || !level->targets || !level->pokemons) {
            printf("Failed to allocate memory for level components\n");
            freeLevel(level);
            return NULL;
        }
        for (int y = 0; y < MAX_HEIGHT + 1; y++) {
            for (int x = 0; x < MAX_WIDTH + 1; x++) {
                if (x == 0 || x == MAX_WIDTH - 1 || y == 0 || y == MAX_HEIGHT - 1) {
                    level->grid[y][x] = '#';
                    level->wallSpriteIndices[y][x] = rand() % 9;
                } else {
                    level->grid[y][x] = ' ';
                    level->wallSpriteIndices[y][x] = -1;
                }
                if (x == MAX_WIDTH)
                    level->grid[y][x] = '\0';
            }
            if (y == MAX_HEIGHT)
                level->grid[y][0] = '\0';
        }
        for (int y = 1; y < MAX_HEIGHT - 1; y++) {
            for (int x = 1; x < MAX_WIDTH - 1; x++) {
                if (rand() % 100 < 30) {
                    level->grid[y][x] = '#';
                    level->wallSpriteIndices[y][x] = rand() % 9;
                }
            }
        }
        level->player = getRandomEmptyPosition(level);
        level->grid[level->player.y][level->player.x] = 'P';
        for (int i = 0; i < level->numBoxes; i++) {
            do
                level->boxes[i] = getRandomEmptyPosition(level);
            while (level->grid[level->boxes[i].y][level->boxes[i].x] == 'T');
            level->grid[level->boxes[i].y][level->boxes[i].x] = 'B';

            do
                level->targets[i] = getRandomEmptyPosition(level);
            while (level->grid[level->targets[i].y][level->targets[i].x] == 'B');
            level->grid[level->targets[i].y][level->targets[i].x] = 'T';
        }
        for (int i = 0; i < numPokemons; i++) {
            level->pokemons[i] = getRandomEmptyPositionForPokemon();
        }
        solvable = isMapSolvable(level);
        if (!solvable)
            freeLevel(level);
    }
    return level;
}

void renderLevel(sfRenderWindow* window, Level* level, Assets assets, int numPokemons)
{
    float offsetX = (WINDOW_WIDTH - MAX_WIDTH * TILE_SIZE) / 2;
    float offsetY = (WINDOW_HEIGHT - MAX_HEIGHT * TILE_SIZE) / 2;
    sfVector2f playerPos;
    sfVector2f pos;
    static int frame = 0;
    static int frameCounter = 0;
    const int frameDelay = 10;

    sfSprite_setPosition(assets.backgroundSprite, (sfVector2f){0, 0});
    sfRenderWindow_drawSprite(window, assets.backgroundSprite, NULL);

    for (int y = 0; y < MAX_HEIGHT; y++) {
        for (int x = 0; x < MAX_WIDTH; x++) {
            pos = (sfVector2f){x * TILE_SIZE + offsetX, y * TILE_SIZE + offsetY};
            switch (level->grid[y][x]) {
                case 'T':
                    sfSprite_setPosition(assets.targetSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.targetSprite, NULL);
                    break;
                case '#':
                    sfSprite_setPosition(assets.floorSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.floorSprite, NULL);
                    int wallSpriteIndex = level->wallSpriteIndices[y][x];
                    sfIntRect wallRect = { (wallSpriteIndex % 3) * 50, (wallSpriteIndex / 3) * 50, 50, 50 };
                    sfSprite_setTextureRect(assets.wallSprite, wallRect);
                    sfSprite_setPosition(assets.wallSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.wallSprite, NULL);
                    break;
                case 'B':
                    sfSprite_setPosition(assets.floorSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.floorSprite, NULL);
                    sfSprite_setPosition(assets.boxSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.boxSprite, NULL);
                    break;
                case ' ':
                    sfSprite_setPosition(assets.floorSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.floorSprite, NULL);
                    break;
                case 'P':
                    sfSprite_setPosition(assets.floorSprite, pos);
                    sfRenderWindow_drawSprite(window, assets.floorSprite, NULL);
                    break;
                default:
                    break;
            }
        }
    }

    if (frameCounter >= frameDelay) {
        frame = (frame + 1) % 4;
        frameCounter = 0;
    } else
        frameCounter++;
    for (int i = 0; i < numPokemons; i++) {
        sfSprite_setScale(assets.pokemonSprites[i], (sfVector2f){2, 2});
        sfIntRect rect = {frame * 50, 0, 50, 50};
        sfSprite_setTextureRect(assets.pokemonSprites[i], rect);
        sfRenderWindow_drawSprite(window, assets.pokemonSprites[i], NULL);
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
        if (!isValid(pushX, pushY) || level->grid[pushY][pushX] == '#' || level->grid[pushY][pushX] == 'B')
            return false;

        isOnTarget = (level->grid[pushY][pushX] == 'T');

        level->grid[level->boxes[boxIndex].y][level->boxes[boxIndex].x] = ' ';
        level->boxes[boxIndex].x = pushX;
        level->boxes[boxIndex].y = pushY;

        if (isOnTarget) {
            level->grid[pushY][pushX] = ' ';
            for (int i = boxIndex; i < level->numBoxes - 1; i++)
                level->boxes[i] = level->boxes[i + 1];
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
    if (level) {
        if (level->boxes)
            free(level->boxes);
        if (level->targets)
            free(level->targets);
        free(level);
    }
}

void freeAssets(Assets assets)
{
    if (assets.playerSprite)
        sfSprite_destroy(assets.playerSprite);
    if (assets.backgroundSprite)
        sfSprite_destroy(assets.backgroundSprite);
    if (assets.boxSprite)
        sfSprite_destroy(assets.boxSprite);
    if (assets.targetSprite)
        sfSprite_destroy(assets.targetSprite);
    if (assets.floorSprite)
        sfSprite_destroy(assets.floorSprite);
    if (assets.wallSprite)
        sfSprite_destroy(assets.wallSprite);
    for (int i = 0; i < 6; i++) {
        if (assets.pokemonSprites[i])
            sfSprite_destroy(assets.pokemonSprites[i]);
        if (assets.pokemonTextures[i])
            sfTexture_destroy(assets.pokemonTextures[i]);
    }
}
