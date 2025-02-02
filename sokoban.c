/*
** EPITECH PROJECT, 2024
** test
** File description:
** sokoban.c
*/

#include "include/sokoban.h"

bool isValid(int x, int y) {
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

    do {
        level = (Level*)malloc(sizeof(Level));
        level->numBoxes = minBoxes + rand() % (maxBoxes - minBoxes + 1);
        level->boxes = (Position*)malloc(level->numBoxes * sizeof(Position));
        level->targets = (Position*)malloc(level->numBoxes * sizeof(Position));
        
        for (int y = 0; y < MAX_HEIGHT; y++) {
            for (int x = 0; x < MAX_WIDTH; x++) {
                if (x == 0 || x == MAX_WIDTH-1 || y == 0 || y == MAX_HEIGHT-1)
                    level->grid[y][x] = '#';
                else
                    level->grid[y][x] = ' ';
            }
        }
        for (int y = 1; y < MAX_HEIGHT-1; y++) {
            for (int x = 1; x < MAX_WIDTH-1; x++) {
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
    } while (!isMapSolvable(level));
    return level;
}

Assets loadAssets()
{
    Assets assets;
    float scale = (float)TILE_SIZE / SPRITE_SIZE;
    sfTexture* playerTexture = sfTexture_createFromFile("assets/player.png", NULL);
    sfTexture* wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
    sfTexture* boxTexture = sfTexture_createFromFile("assets/box.png", NULL);
    sfTexture* targetTexture = sfTexture_createFromFile("assets/storage.png", NULL);
    sfTexture* floorTexture = sfTexture_createFromFile("assets/floor.png", NULL);
    sfVector2f spriteScale = {scale, scale};

    assets.playerSprite = sfSprite_create();
    assets.wallSprite = sfSprite_create();
    assets.boxSprite = sfSprite_create();
    assets.targetSprite = sfSprite_create();
    assets.floorSprite = sfSprite_create();
    
    sfSprite_setTexture(assets.playerSprite, playerTexture, sfTrue);
    sfSprite_setTexture(assets.wallSprite, wallTexture, sfTrue);
    sfSprite_setTexture(assets.boxSprite, boxTexture, sfTrue);
    sfSprite_setTexture(assets.targetSprite, targetTexture, sfTrue);
    sfSprite_setTexture(assets.floorSprite, floorTexture, sfTrue);
    
    sfSprite_setScale(assets.playerSprite, spriteScale);
    sfSprite_setScale(assets.wallSprite, spriteScale);
    sfSprite_setScale(assets.boxSprite, spriteScale);
    sfSprite_setScale(assets.targetSprite, spriteScale);
    sfSprite_setScale(assets.floorSprite, spriteScale);
    
    return assets;
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

void saveScore(Player player)
{
    char name[MAX_NAME_LENGTH];
    int score;
    char buffer[256];
    char newContent[2048] = "";
    bool playerFound = false;

    FILE* file = fopen("scores.txt", "r");
    if (!file) {
        file = fopen("scores.txt", "w");
        fprintf(file, "Player: %s, Score: %d\n", player.playerName, player.score);
        fclose(file);
        return;
    }

    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "Player: %[^,], Score: %d", name, &score) == 2) {
            if (strcmp(name, player.playerName) == 0) {
                sprintf(buffer, "Player: %s, Score: %d\n", player.playerName, player.score);
                playerFound = true;
            }
        }
        strcat(newContent, buffer);
    }
    fclose(file);
    if (!playerFound) {
        sprintf(buffer, "Player: %s, Score: %d\n", player.playerName, player.score);
        strcat(newContent, buffer);
    }
    file = fopen("scores.txt", "w");
    fputs(newContent, file);
    fclose(file);
}

void displayMenu(sfRenderWindow* window, sfFont* font, Player* player)
{
    sfVector2f mousePos;
    sfText* promptText = sfText_create();
    sfFloatRect button1Bounds;
    sfFloatRect button2Bounds;
    sfEvent event;
    bool menuOpen = true;
    sfRectangleShape* button1 = sfRectangleShape_create();
    sfText* buttonText1 = sfText_create();
    sfRectangleShape* button2 = sfRectangleShape_create();
    sfText* buttonText2 = sfText_create();

    sfText_setFont(promptText, font);
    sfText_setCharacterSize(promptText, 24);
    sfText_setColor(promptText, sfBlack);
    sfText_setString(promptText, "Level Complete!\n1. Play again ?\n2. Quit");
    sfText_setPosition(promptText, (sfVector2f){WINDOW_WIDTH / 4 + 50, WINDOW_HEIGHT / 4});

    sfRectangleShape_setSize(button1, (sfVector2f){200, 40});
    sfRectangleShape_setFillColor(button1, sfGreen);
    sfRectangleShape_setPosition(button1, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 100});

    sfText_setFont(buttonText1, font);
    sfText_setCharacterSize(buttonText1, 24);
    sfText_setColor(buttonText1, sfBlack);
    sfText_setString(buttonText1, "Play Again ?");
    sfText_setPosition(buttonText1, (sfVector2f){WINDOW_WIDTH / 4 + 40, WINDOW_HEIGHT / 4 + 105});

    sfRectangleShape_setSize(button2, (sfVector2f){200, 40});
    sfRectangleShape_setFillColor(button2, sfGreen);
    sfRectangleShape_setPosition(button2, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 150});

    sfText_setFont(buttonText2, font);
    sfText_setCharacterSize(buttonText2, 24);
    sfText_setColor(buttonText2, sfBlack);
    sfText_setString(buttonText2, "Quit");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 4 + 75, WINDOW_HEIGHT / 4 + 155});

    while (menuOpen) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                menuOpen = false;
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfRectangleShape_getGlobalBounds(button1);
                    button2Bounds = sfRectangleShape_getGlobalBounds(button2);
                    if (sfFloatRect_contains(&button1Bounds, mousePos.x, mousePos.y)) {
                        saveScore(*player);
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        sfRenderWindow_close(window);
                        menuOpen = false;
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, promptText, NULL);
        sfRenderWindow_drawRectangleShape(window, button1, NULL);
        sfRenderWindow_drawText(window, buttonText1, NULL);
        sfRenderWindow_drawRectangleShape(window, button2, NULL);
        sfRenderWindow_drawText(window, buttonText2, NULL);
        sfRenderWindow_display(window);
    }
    sfText_destroy(promptText);
    sfText_destroy(buttonText1);
    sfText_destroy(buttonText2);
    sfRectangleShape_destroy(button1);
    sfRectangleShape_destroy(button2);
}

void askPlayerName(sfRenderWindow* window, sfFont* font, Player* player)
{
    sfEvent event;
    sfText* promptText = sfText_create();
    sfText* nameText = sfText_create();
    sfRectangleShape* inputBox = sfRectangleShape_create();
    sfRectangleShape* button = sfRectangleShape_create();
    sfText* buttonText = sfText_create();
    bool nameEntered = false;
    char name[MAX_NAME_LENGTH] = "";
    int nameLength = 0;
    sfVector2f mousePos;
    sfFloatRect buttonBounds;

    sfText_setFont(promptText, font);
    sfText_setCharacterSize(promptText, 24);
    sfText_setColor(promptText, sfBlack);
    sfText_setString(promptText, "Enter your name:");
    sfText_setPosition(promptText, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4});

    sfText_setFont(nameText, font);
    sfText_setCharacterSize(nameText, 24);
    sfText_setColor(nameText, sfBlack);
    sfText_setPosition(nameText, (sfVector2f){WINDOW_WIDTH / 4 + 10, WINDOW_HEIGHT / 4 + 55});

    sfRectangleShape_setSize(inputBox, (sfVector2f){300, 40});
    sfRectangleShape_setOutlineColor(inputBox, sfWhite);
    sfRectangleShape_setOutlineThickness(inputBox, 2);
    sfRectangleShape_setPosition(inputBox, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 50});

    sfRectangleShape_setSize(button, (sfVector2f){100, 40});
    sfRectangleShape_setFillColor(button, sfGreen);
    sfRectangleShape_setPosition(button, (sfVector2f){WINDOW_WIDTH / 4 + 320, WINDOW_HEIGHT / 4 + 50});

    sfText_setFont(buttonText, font);
    sfText_setCharacterSize(buttonText, 24);
    sfText_setColor(buttonText, sfBlack);
    sfText_setString(buttonText, "OK");
    sfText_setPosition(buttonText, (sfVector2f){WINDOW_WIDTH / 4 + 350, WINDOW_HEIGHT / 4 + 55});

    while (!nameEntered) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                nameEntered = true;
            }
            if (event.type == sfEvtTextEntered) {
                if (event.text.unicode == '\r')
                    nameEntered = true;
                else if (event.text.unicode == '\b') {
                    if (nameLength > 0)
                        name[--nameLength] = '\0';
                } else if (nameLength < MAX_NAME_LENGTH - 1) {
                    name[nameLength++] = (char)event.text.unicode;
                    name[nameLength] = '\0';
                }
                sfText_setString(nameText, name);
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    buttonBounds = sfRectangleShape_getGlobalBounds(button);
                    if (sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y))
                        nameEntered = true;
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawRectangleShape(window, inputBox, NULL);
        sfRenderWindow_drawRectangleShape(window, button, NULL);
        sfRenderWindow_drawText(window, nameText, NULL);
        sfRenderWindow_drawText(window, buttonText, NULL);
        sfRenderWindow_drawText(window, promptText, NULL);
        sfRenderWindow_display(window);
    }

    strncpy(player->playerName, name, MAX_NAME_LENGTH);
    sfText_destroy(promptText);
    sfText_destroy(nameText);
    sfText_destroy(buttonText);
    sfRectangleShape_destroy(inputBox);
    sfRectangleShape_destroy(button);
}

int selectDifficulty(sfRenderWindow* window, sfFont* font)
{
    sfVector2f mousePos;
    sfText* promptText = sfText_create();
    sfRectangleShape* button1;
    sfText* buttonText1;
    sfRectangleShape* button2;
    sfText* buttonText2;
    sfRectangleShape* button3;
    sfText* buttonText3;
    sfRectangleShape* button4;
    sfText* buttonText4;
    int difficulty = 0;
    bool difficultySelected = false;
    sfEvent event;
    sfFloatRect button1Bounds;
    sfFloatRect button2Bounds;
    sfFloatRect button3Bounds;
    sfFloatRect button4Bounds;

    sfText_setFont(promptText, font);
    sfText_setCharacterSize(promptText, 24);
    sfText_setColor(promptText, sfBlack);
    sfText_setString(promptText, "Select Difficulty:\n1. Easy\n2. Normal\n3. Hard\n4. Hell");
    sfText_setPosition(promptText, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4});

    button1 = sfRectangleShape_create();
    sfRectangleShape_setSize(button1, (sfVector2f){100, 40});
    sfRectangleShape_setFillColor(button1, sfGreen);
    sfRectangleShape_setPosition(button1, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 100});

    buttonText1 = sfText_create();
    sfText_setFont(buttonText1, font);
    sfText_setCharacterSize(buttonText1, 24);
    sfText_setColor(buttonText1, sfBlack);
    sfText_setString(buttonText1, "Easy");
    sfText_setPosition(buttonText1, (sfVector2f){WINDOW_WIDTH / 4 + 25, WINDOW_HEIGHT / 4 + 105});

    button2 = sfRectangleShape_create();
    sfRectangleShape_setSize(button2, (sfVector2f){100, 40});
    sfRectangleShape_setFillColor(button2, sfGreen);
    sfRectangleShape_setPosition(button2, (sfVector2f){WINDOW_WIDTH / 4 + 120, WINDOW_HEIGHT / 4 + 100});

    buttonText2 = sfText_create();
    sfText_setFont(buttonText2, font);
    sfText_setCharacterSize(buttonText2, 24);
    sfText_setColor(buttonText2, sfBlack);
    sfText_setString(buttonText2, "Normal");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 4 + 125, WINDOW_HEIGHT / 4 + 105});

    button3 = sfRectangleShape_create();
    sfRectangleShape_setSize(button3, (sfVector2f){100, 40});
    sfRectangleShape_setFillColor(button3, sfGreen);
    sfRectangleShape_setPosition(button3, (sfVector2f){WINDOW_WIDTH / 4 + 240, WINDOW_HEIGHT / 4 + 100});

    buttonText3 = sfText_create();
    sfText_setFont(buttonText3, font);
    sfText_setCharacterSize(buttonText3, 24);
    sfText_setColor(buttonText3, sfBlack);
    sfText_setString(buttonText3, "Hard");
    sfText_setPosition(buttonText3, (sfVector2f){WINDOW_WIDTH / 4 + 260, WINDOW_HEIGHT / 4 + 105});

    button4 = sfRectangleShape_create();
    sfRectangleShape_setSize(button4, (sfVector2f){100, 40});
    sfRectangleShape_setFillColor(button4, sfGreen);
    sfRectangleShape_setPosition(button4, (sfVector2f){WINDOW_WIDTH / 4 + 360, WINDOW_HEIGHT / 4 + 100});

    buttonText4 = sfText_create();
    sfText_setFont(buttonText4, font);
    sfText_setCharacterSize(buttonText4, 24);
    sfText_setColor(buttonText4, sfBlack);
    sfText_setString(buttonText4, "Hell");
    sfText_setPosition(buttonText4, (sfVector2f){WINDOW_WIDTH / 4 + 385, WINDOW_HEIGHT / 4 + 105});

    while (!difficultySelected) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                difficultySelected = true;
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfRectangleShape_getGlobalBounds(button1);
                    button2Bounds = sfRectangleShape_getGlobalBounds(button2);
                    button3Bounds = sfRectangleShape_getGlobalBounds(button3);
                    button4Bounds = sfRectangleShape_getGlobalBounds(button4);
                    if (sfFloatRect_contains(&button1Bounds, mousePos.x, mousePos.y)) {
                        difficulty = 1;
                        difficultySelected = true;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        difficulty = 2;
                        difficultySelected = true;
                    } else if (sfFloatRect_contains(&button3Bounds, mousePos.x, mousePos.y)) {
                        difficulty = 3;
                        difficultySelected = true;
                    } else if (sfFloatRect_contains(&button4Bounds, mousePos.x, mousePos.y)) {
                        difficulty = 4;
                        difficultySelected = true;
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawText(window, promptText, NULL);
        sfRenderWindow_drawRectangleShape(window, button1, NULL);
        sfRenderWindow_drawText(window, buttonText1, NULL);
        sfRenderWindow_drawRectangleShape(window, button2, NULL);
        sfRenderWindow_drawText(window, buttonText2, NULL);
        sfRenderWindow_drawRectangleShape(window, button3, NULL);
        sfRenderWindow_drawText(window, buttonText3, NULL);
        sfRenderWindow_drawRectangleShape(window, button4, NULL);
        sfRenderWindow_drawText(window, buttonText4, NULL);
        sfRenderWindow_display(window);
    }
    sfText_destroy(promptText);
    sfText_destroy(buttonText1);
    sfText_destroy(buttonText2);
    sfText_destroy(buttonText3);
    sfText_destroy(buttonText4);
    sfRectangleShape_destroy(button1);
    sfRectangleShape_destroy(button2);
    sfRectangleShape_destroy(button3);
    sfRectangleShape_destroy(button4);
    return difficulty;
}

int getNumBoxesForDifficulty(int difficulty) {
    switch (difficulty) {
        case 1:
            return MIN_BOXES + rand() % 2;
        case 2:
            return 2 + rand() % 2;
        case 3:
            return 3 + rand() % 2;
        case 4:
            return 5 + rand() % 6;
        default:
            return MIN_BOXES;
    }
}

int main(void)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Sokoban", sfResize | sfClose, NULL);
    sfView* view;
    sfEvent event;
    Level* level;
    int minBoxes;
    int maxBoxes;
    int difficulty;
    Player player = {"", 0};
    Assets assets;
    sfFont* font = sfFont_createFromFile("assets/font.ttf");

    srand(time(NULL));
    sfRenderWindow_setFramerateLimit(window, 60);
    if (!font) {
        printf("Failed to load font\n");
        return -1;
    }
    assets = loadAssets();
    askPlayerName(window, font, &player);
    difficulty = selectDifficulty(window, font);
    switch (difficulty) {
        case 1:
            minBoxes = 1;
            maxBoxes = 5;
            break;
        case 2:
            minBoxes = 5;
            maxBoxes = 10;
            break;
        case 3:
            minBoxes = 10;
            maxBoxes = 15;
            break;
        case 4:
            minBoxes = 15;
            maxBoxes = 20;
            break;
        default:
            minBoxes = 1;
            maxBoxes = 5;
            break;
    }
    level = generateLevel(minBoxes, maxBoxes);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
            }
            if (event.type == sfEvtResized) {
                view = sfView_createFromRect((sfFloatRect){0, 0, event.size.width, event.size.height});
                sfRenderWindow_setView(window, view);
                sfView_destroy(view);
            }
            if (event.type == sfEvtKeyPressed) {
                switch (event.key.code) {
                    case sfKeyUp:
                        movePlayer(level, 0, -1);
                        break;
                    case sfKeyDown:
                        movePlayer(level, 0, 1);
                        break;
                    case sfKeyLeft:
                        movePlayer(level, -1, 0);
                        break;
                    case sfKeyRight:
                        movePlayer(level, 1, 0);
                        break;
                    case sfKeyR:
                        freeLevel(level);
                        level = generateLevel(minBoxes, maxBoxes);
                        break;
                    case sfKeyEscape:
                        displayMenu(window, font, &player);
                        break;
                    default:
                        break;
                }
                if (checkWin(level)) {
                    player.score += 100;
                    displayMenu(window, font, &player);
                    freeLevel(level);
                    level = generateLevel(minBoxes, maxBoxes);
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        renderLevel(window, level, assets);
        sfRenderWindow_display(window);
    }
    freeLevel(level);
    freeAssets(assets);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);
    return 0;
}