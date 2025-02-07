/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** menus.c
*/

#include "../include/sokoban.h"

sfTexture* customCharacter(sfRenderWindow* window, Assets assets)
{
    sfFont* font = sfFont_createFromFile("assets/font.ttf");
    sfTexture* characterTextures[10];
    sfSprite* characterSprites[10];
    sfRectangleShape* leftArrows[10];
    sfRectangleShape* rightArrows[10];
    sfText* titleText = sfText_create();
    sfEvent event;
    sfVector2f mousePos;
    sfFloatRect buttonBounds;
    bool menuOpen = true;
    char* characterFiles[10] = {
        "assets/characters/male1.png",
        "assets/characters/male2.png",
        "assets/characters/male3.png",
        "assets/characters/male4.png",
        "assets/characters/male5.png",
        "assets/characters/female1.png",
        "assets/characters/female2.png",
        "assets/characters/female3.png",
        "assets/characters/female4.png",
        "assets/characters/female5.png"
    };
    int textureIndex = 0;
    sfFloatRect titleBounds;
    sfIntRect rect = {0, 0, 50, 50};
    sfTexture* backgroundTexture = sfTexture_createFromFile("assets/menu/menu_persos.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();

    if (!backgroundTexture || !backgroundSprite || !font || !titleText)
        return NULL;
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
    for (int i = 0; i < 10; i++) {
        characterTextures[i] = sfTexture_createFromFile(characterFiles[i], NULL);
        characterSprites[i] = sfSprite_create();
        if (!characterTextures[i] || !characterSprites[i])
            return NULL;
        sfSprite_setTexture(characterSprites[i], characterTextures[i], sfTrue);
        sfSprite_setTextureRect(characterSprites[i], rect);
        sfSprite_setScale(characterSprites[i], (sfVector2f){4.0f, 4.0f});
        leftArrows[i] = sfRectangleShape_create();
        if (!leftArrows[i])
            return NULL;
        sfRectangleShape_setSize(leftArrows[i], (sfVector2f){30, 250});
        sfRectangleShape_setFillColor(leftArrows[i], sfBlack);
        rightArrows[i] = sfRectangleShape_create();
        if (!rightArrows[i])
            return NULL;
        sfRectangleShape_setSize(rightArrows[i], (sfVector2f){30, 250});
        sfRectangleShape_setFillColor(rightArrows[i], sfBlack);
    }
    sfRectangleShape_setPosition(leftArrows[0], (sfVector2f){175, 186});
    sfRectangleShape_setPosition(rightArrows[0], (sfVector2f){385, 186});
    sfRectangleShape_setPosition(leftArrows[1], (sfVector2f){505, 186});
    sfRectangleShape_setPosition(rightArrows[1], (sfVector2f){715, 186});
    sfRectangleShape_setPosition(leftArrows[2], (sfVector2f){840, 186});
    sfRectangleShape_setPosition(rightArrows[2], (sfVector2f){1050, 186});
    sfRectangleShape_setPosition(leftArrows[3], (sfVector2f){1170, 186});
    sfRectangleShape_setPosition(rightArrows[3], (sfVector2f){1380, 186});
    sfRectangleShape_setPosition(leftArrows[4], (sfVector2f){1500, 186});
    sfRectangleShape_setPosition(rightArrows[4], (sfVector2f){1710, 186});
    sfRectangleShape_setPosition(leftArrows[5], (sfVector2f){175, 624});
    sfRectangleShape_setPosition(rightArrows[5], (sfVector2f){385, 624});
    sfRectangleShape_setPosition(leftArrows[6], (sfVector2f){505, 624});
    sfRectangleShape_setPosition(rightArrows[6], (sfVector2f){715, 624});
    sfRectangleShape_setPosition(leftArrows[7], (sfVector2f){840, 624});
    sfRectangleShape_setPosition(rightArrows[7], (sfVector2f){1050, 624});
    sfRectangleShape_setPosition(leftArrows[8], (sfVector2f){1170, 624});
    sfRectangleShape_setPosition(rightArrows[8], (sfVector2f){1380, 624});
    sfRectangleShape_setPosition(leftArrows[9], (sfVector2f){1500, 624});
    sfRectangleShape_setPosition(rightArrows[9], (sfVector2f){1710, 624});
    sfSprite_setPosition(characterSprites[0], (sfVector2f){195, 220});
    sfSprite_setPosition(characterSprites[1], (sfVector2f){525, 220});
    sfSprite_setPosition(characterSprites[2], (sfVector2f){860, 210});
    sfSprite_setPosition(characterSprites[3], (sfVector2f){1190, 210});
    sfSprite_setPosition(characterSprites[4], (sfVector2f){1520, 215});
    sfSprite_setPosition(characterSprites[5], (sfVector2f){195, 640});
    sfSprite_setPosition(characterSprites[6], (sfVector2f){525, 640});
    sfSprite_setPosition(characterSprites[7], (sfVector2f){860, 640});
    sfSprite_setPosition(characterSprites[8], (sfVector2f){1185, 640});
    sfSprite_setPosition(characterSprites[9], (sfVector2f){1520, 630});
    sfText_setFont(titleText, font);
    sfText_setString(titleText, "Choose your Character");
    sfText_setCharacterSize(titleText, 48);
    sfText_setColor(titleText, sfBlack);
    titleBounds = sfText_getGlobalBounds(titleText);
    sfText_setPosition(titleText, (sfVector2f){(1920 - titleBounds.width) / 2, 50});
    while (menuOpen) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                menuOpen = false;
                return NULL;
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    for (int i = 0; i < 10; i++) {
                        buttonBounds = sfRectangleShape_getGlobalBounds(leftArrows[i]);
                        if (sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y)) {
                            sfIntRect textureRect = sfSprite_getTextureRect(characterSprites[i]);
                            textureRect.top = (textureRect.top - 50 + sfTexture_getSize(characterTextures[i]).y) % sfTexture_getSize(characterTextures[i]).y;
                            sfSprite_setTextureRect(characterSprites[i], textureRect);
                        }
                        buttonBounds = sfRectangleShape_getGlobalBounds(rightArrows[i]);
                        if (sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y)) {
                            sfIntRect textureRect = sfSprite_getTextureRect(characterSprites[i]);
                            textureRect.top = (textureRect.top + 50) % sfTexture_getSize(characterTextures[i]).y;
                            sfSprite_setTextureRect(characterSprites[i], textureRect);
                        }
                        buttonBounds = sfSprite_getGlobalBounds(characterSprites[i]);
                        if (sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y))
                            return characterTextures[i];
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        sfRenderWindow_drawText(window, titleText, NULL);
        for (int i = 0; i < 10; i++) {
            sfRenderWindow_drawSprite(window, characterSprites[i], NULL);
            sfRenderWindow_drawRectangleShape(window, leftArrows[i], NULL);
            sfRenderWindow_drawRectangleShape(window, rightArrows[i], NULL);
        }
        sfRenderWindow_display(window);
    }
    return NULL;
}

int displayGameMenu(sfRenderWindow *window, Assets *assets, sfMusic* menuMusic, GameSettings* game_set, sfMusic* levelMusic)
{
    sfTexture* texture = sfTexture_createFromFile("assets/menu/menu_background.png", NULL);
    sfSprite* sprite_menu = sfSprite_create();
    sfRectangleShape* button1 = sfRectangleShape_create();
    sfRectangleShape* button2 = sfRectangleShape_create();
    sfRectangleShape* button3 = sfRectangleShape_create();
    sfEvent event;
    sfVector2f mousePos;
    sfFloatRect button1Bounds;
    sfFloatRect button2Bounds;
    sfFloatRect button3Bounds;
    bool menuOpen = true;
    int returned = 0;

    if (!texture || !sprite_menu || !button1 || !button2 || !button3) {
        printf("Failed to load menu background\n");
        return -1;
    }
    sfSprite_setTexture(sprite_menu, texture, sfTrue);
    sfRectangleShape_setSize(button1, (sfVector2f){205, 135});
    sfRectangleShape_setPosition(button1, (sfVector2f){855, 480});
    sfRectangleShape_setOutlineColor(button1, sfTransparent);
    sfRectangleShape_setOutlineThickness(button1, 2);
    sfRectangleShape_setFillColor(button1, sfTransparent);
    sfRectangleShape_setSize(button2, (sfVector2f){260, 125});
    sfRectangleShape_setPosition(button2, (sfVector2f){830, 635});
    sfRectangleShape_setOutlineColor(button2, sfTransparent);
    sfRectangleShape_setOutlineThickness(button2, 2);
    sfRectangleShape_setFillColor(button2, sfTransparent);
    sfRectangleShape_setSize(button3, (sfVector2f){225, 130});
    sfRectangleShape_setPosition(button3, (sfVector2f){845, 780});
    sfRectangleShape_setOutlineColor(button3, sfTransparent);
    sfRectangleShape_setOutlineThickness(button3, 2);
    sfRectangleShape_setFillColor(button3, sfTransparent);
    while (menuOpen) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                menuOpen = false;
                returned = -1;
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfRectangleShape_getGlobalBounds(button1);
                    button2Bounds = sfRectangleShape_getGlobalBounds(button2);
                    button3Bounds = sfRectangleShape_getGlobalBounds(button3);
                    if (sfFloatRect_contains(&button1Bounds, mousePos.x, mousePos.y)) {
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        if (settings(window, game_set, menuMusic, NULL) == -1) {
                            sfRenderWindow_destroy(window);
                            exit(0);
                        }
                    } else if (sfFloatRect_contains(&button3Bounds, mousePos.x, mousePos.y)) {
                        sfRenderWindow_close(window);
                        returned = -1;
                        menuOpen = false;
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, sprite_menu, NULL);
        sfRenderWindow_drawRectangleShape(window, button1, NULL);
        sfRenderWindow_drawRectangleShape(window, button2, NULL);
        sfRenderWindow_drawRectangleShape(window, button3, NULL);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(button1);
    sfRectangleShape_destroy(button2);
    sfRectangleShape_destroy(button3);
    sfSprite_destroy(sprite_menu);
    sfTexture_destroy(texture);
    if (returned == -1)
        sfRenderWindow_destroy(window);

    return returned;
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

void loadScore(Player* player)
{
    char name[MAX_NAME_LENGTH];
    int score;
    char buffer[256];
    bool playerFound = false;

    FILE* file = fopen("scores.txt", "r");
    if (!file) {
        player->score = 0;
        return;
    }
    while (fgets(buffer, sizeof(buffer), file)) {
        if (sscanf(buffer, "Player: %[^,], Score: %d", name, &score) == 2) {
            if (strcmp(name, player->playerName) == 0) {
                player->score = score;
                playerFound = true;
                break;
            }
        }
    }
    fclose(file);
    if (!playerFound)
        player->score = 0;
}

void displayWinMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level, int* minBoxes, int* maxBoxes, Assets* assets, int* numPokemons, sfMusic* menuMusic)
{
    sfVector2f mousePos;
    sfFloatRect button1Bounds;
    sfFloatRect button2Bounds;
    sfFloatRect button3Bounds;
    sfEvent event;
    bool menuOpen = true;
    sfRectangleShape* button1 = sfRectangleShape_create();
    sfText* buttonText1 = sfText_create();
    sfRectangleShape* button2 = sfRectangleShape_create();
    sfText* buttonText2 = sfText_create();
    sfRectangleShape* button3 = sfRectangleShape_create();
    sfText* buttonText3 = sfText_create();
    int newDifficulty;
    Assets newAssets;
    sfTexture* backgroundTexture = sfTexture_createFromFile("assets/menu/menu_esc.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();
    static int moveCounter = 0;

    if (!backgroundTexture || !backgroundSprite || !button1 || !button2 || !button3 || !buttonText1 || !buttonText2 || !buttonText3)
        return;
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
    sfSprite_setPosition(backgroundSprite, (sfVector2f){0, 0});
    sfRectangleShape_setSize(button1, (sfVector2f){380, 75});
    sfRectangleShape_setFillColor(button1, sfTransparent);
    sfRectangleShape_setPosition(button1, (sfVector2f){WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 4 + 210});
    sfText_setFont(buttonText1, font);
    sfText_setCharacterSize(buttonText1, 45);
    sfText_setColor(buttonText1, sfBlack);
    sfText_setString(buttonText1, "Play Again ?");
    sfText_setPosition(buttonText1, (sfVector2f){WINDOW_WIDTH / 2 - 170, WINDOW_HEIGHT / 4 + 215});
    sfRectangleShape_setSize(button2, (sfVector2f){380, 75});
    sfRectangleShape_setFillColor(button2, sfTransparent);
    sfRectangleShape_setPosition(button2, (sfVector2f){WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 4 + 310});
    sfText_setFont(buttonText2, font);
    sfText_setCharacterSize(buttonText2, 45);
    sfText_setColor(buttonText2, sfBlack);
    sfText_setString(buttonText2, "Difficulty");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 2 - 140, WINDOW_HEIGHT / 4 + 315});
    sfRectangleShape_setSize(button3, (sfVector2f){380, 75});
    sfRectangleShape_setFillColor(button3, sfTransparent);
    sfRectangleShape_setPosition(button3, (sfVector2f){WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 4 + 410});
    sfText_setFont(buttonText3, font);
    sfText_setCharacterSize(buttonText3, 50);
    sfText_setColor(buttonText3, sfBlack);
    sfText_setString(buttonText3, "Quit");
    sfText_setPosition(buttonText3, (sfVector2f){WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 4 + 415});
    while (menuOpen) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                menuOpen = false;
            }
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
                menuOpen = false;
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfRectangleShape_getGlobalBounds(button1);
                    button2Bounds = sfRectangleShape_getGlobalBounds(button2);
                    button3Bounds = sfRectangleShape_getGlobalBounds(button3);
                    if (sfFloatRect_contains(&button1Bounds, mousePos.x, mousePos.y)) {
                        freeLevel(*level);
                        *level = generateLevel(*minBoxes, *maxBoxes, *numPokemons);
                        moveCounter = 0;
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        newDifficulty = selectDifficulty(window, font);
                        player->difficulty = newDifficulty;
                        switch (player->difficulty) {
                            case 1:
                                *minBoxes = 1;
                                *maxBoxes = 5;
                                *numPokemons = 4;
                                break;
                            case 2:
                                *minBoxes = 6;
                                *maxBoxes = 10;
                                *numPokemons = 5;
                                break;
                            case 3:
                                *minBoxes = 11;
                                *maxBoxes = 15;
                                *numPokemons = 4;
                                break;
                            case 4:
                                *minBoxes = 16;
                                *maxBoxes = 20;
                                *numPokemons = 3;
                                break;
                            default:
                                *minBoxes = 1;
                                *maxBoxes = 5;
                                *numPokemons = 4;
                                break;
                        }
                        freeLevel(*level);
                        *level = generateLevel(*minBoxes, *maxBoxes, *numPokemons);
                        if (assets->levelMusic != NULL) {
                            sfMusic_stop(assets->levelMusic);
                            sfMusic_destroy(assets->levelMusic);
                            assets->levelMusic = NULL;
                        }
                        freeAssets(*assets);
                        *assets = loadAssets(player->difficulty, window);
                        if (assets->levelMusic) {
                            sfMusic_setLoop(assets->levelMusic, sfTrue);
                            sfMusic_play(assets->levelMusic);
                        }
                        moveCounter = 0;
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button3Bounds, mousePos.x, mousePos.y)) {
                        sfRenderWindow_close(window);
                        menuOpen = false;
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        sfRenderWindow_drawRectangleShape(window, button1, NULL);
        sfRenderWindow_drawText(window, buttonText1, NULL);
        sfRenderWindow_drawRectangleShape(window, button2, NULL);
        sfRenderWindow_drawText(window, buttonText2, NULL);
        sfRenderWindow_drawRectangleShape(window, button3, NULL);
        sfRenderWindow_drawText(window, buttonText3, NULL);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(button1);
    sfText_destroy(buttonText1);
    sfRectangleShape_destroy(button2);
    sfText_destroy(buttonText2);
    sfRectangleShape_destroy(button3);
    sfText_destroy(buttonText3);
    sfTexture_destroy(backgroundTexture);
    sfSprite_destroy(backgroundSprite);
}

void displayPauseMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level, int* minBoxes, int* maxBoxes, Assets* assets, int* numPokemons, sfMusic* menuMusic, GameSettings *setting)
{
    sfVector2f mousePos;
    sfFloatRect button1Bounds;
    sfFloatRect button2Bounds;
    sfFloatRect button3Bounds;
    sfEvent event;
    bool menuOpen = true;
    sfRectangleShape* button1 = sfRectangleShape_create();
    sfText* buttonText1 = sfText_create();
    sfRectangleShape* button2 = sfRectangleShape_create();
    sfText* buttonText2 = sfText_create();
    sfRectangleShape* button3 = sfRectangleShape_create();
    sfText* buttonText3 = sfText_create();
    int newDifficulty;
    Assets newAssets;
    sfTexture* backgroundTexture = sfTexture_createFromFile("assets/menu/menu_esc.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();

    if (!backgroundTexture || !backgroundSprite || !button1 || !button2 || !button3 || !buttonText1 || !buttonText2 || !buttonText3)
        exit(84);
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
    sfSprite_setPosition(backgroundSprite, (sfVector2f){0, 0});
    sfRectangleShape_setSize(button1, (sfVector2f){380, 75});
    sfRectangleShape_setFillColor(button1, sfTransparent);
    sfRectangleShape_setPosition(button1, (sfVector2f){WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 4 + 210});
    sfText_setFont(buttonText1, font);
    sfText_setCharacterSize(buttonText1, 45);
    sfText_setColor(buttonText1, sfBlack);
    sfText_setString(buttonText1, "Resume");
    sfText_setPosition(buttonText1, (sfVector2f){WINDOW_WIDTH / 2 - 105, WINDOW_HEIGHT / 4 + 215});
    sfRectangleShape_setSize(button2, (sfVector2f){380, 75});
    sfRectangleShape_setFillColor(button2, sfTransparent);
    sfRectangleShape_setPosition(button2, (sfVector2f){WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 4 + 310});
    sfText_setFont(buttonText2, font);
    sfText_setCharacterSize(buttonText2, 45);
    sfText_setColor(buttonText2, sfBlack);
    sfText_setString(buttonText2, "Settings");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 2 - 120, WINDOW_HEIGHT / 4 + 310});
    sfRectangleShape_setSize(button3, (sfVector2f){380, 75});
    sfRectangleShape_setFillColor(button3, sfTransparent);
    sfRectangleShape_setPosition(button3, (sfVector2f){WINDOW_WIDTH / 2 - 190, WINDOW_HEIGHT / 4 + 410});
    sfText_setFont(buttonText3, font);
    sfText_setCharacterSize(buttonText3, 50);
    sfText_setColor(buttonText3, sfBlack);
    sfText_setString(buttonText3, "Quit");
    sfText_setPosition(buttonText3, (sfVector2f){WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 4 + 415});
    while (menuOpen) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                menuOpen = false;
            }
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
                menuOpen = false;
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfRectangleShape_getGlobalBounds(button1);
                    button2Bounds = sfRectangleShape_getGlobalBounds(button2);
                    button3Bounds = sfRectangleShape_getGlobalBounds(button3);
                    if (sfFloatRect_contains(&button1Bounds, mousePos.x, mousePos.y)) {
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        if (settings(window, setting, menuMusic, assets->levelMusic) == -1) {
                            sfRenderWindow_destroy(window);
                            exit(0);
                        }
                        apply_sound_settings(setting, menuMusic, assets->levelMusic);
                        sfRenderWindow_clear(window, sfBlack);
                        menuOpen = true;
                    } else if (sfFloatRect_contains(&button3Bounds, mousePos.x, mousePos.y)) {
                        sfRenderWindow_close(window);
                        menuOpen = false;
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        sfRenderWindow_drawRectangleShape(window, button1, NULL);
        sfRenderWindow_drawText(window, buttonText1, NULL);
        sfRenderWindow_drawRectangleShape(window, button2, NULL);
        sfRenderWindow_drawText(window, buttonText2, NULL);
        sfRenderWindow_drawRectangleShape(window, button3, NULL);
        sfRenderWindow_drawText(window, buttonText3, NULL);
        sfRenderWindow_display(window);
    }
    sfRectangleShape_destroy(button1);
    sfText_destroy(buttonText1);
    sfRectangleShape_destroy(button2);
    sfText_destroy(buttonText2);
    sfRectangleShape_destroy(button3);
    sfText_destroy(buttonText3);
    sfTexture_destroy(backgroundTexture);
    sfSprite_destroy(backgroundSprite);
}

void askPlayerName(sfRenderWindow* window, sfFont* font, Player* player)
{
    sfEvent event;
    sfText* nameText = sfText_create();
    sfRectangleShape* button = sfRectangleShape_create();
    sfText* buttonText = sfText_create();
    bool nameEntered = false;
    char name[MAX_NAME_LENGTH] = "";
    int nameLength = 0;
    sfVector2f mousePos;
    sfFloatRect buttonBounds;
    sfTexture* backgroundTexture = sfTexture_createFromFile("assets/menu/menu_username.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();

    if (!backgroundTexture || !backgroundSprite || !nameText || !button || !buttonText)
        return;
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
    sfText_setFont(nameText, font);
    sfText_setCharacterSize(nameText, 100);
    sfText_setColor(nameText, sfBlack);
    sfText_setPosition(nameText, (sfVector2f){WINDOW_WIDTH / 2 - 400, WINDOW_HEIGHT / 2 - 80});
    sfRectangleShape_setSize(button, (sfVector2f){80, 80});
    sfRectangleShape_setFillColor(button, sfTransparent);
    sfRectangleShape_setPosition(button, (sfVector2f){WINDOW_WIDTH / 2 + 440, WINDOW_HEIGHT / 2 - 45});
    sfRectangleShape_setOutlineColor(button, sfBlack);
    sfRectangleShape_setOutlineThickness(button, 10);
    sfText_setFont(buttonText, font);
    sfText_setCharacterSize(buttonText, 30);
    sfText_setColor(buttonText, sfBlack);
    sfText_setString(buttonText, "OK");
    sfText_setPosition(buttonText, (sfVector2f){WINDOW_WIDTH / 2 + 455, WINDOW_HEIGHT / 2 - 25});
    while (!nameEntered) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                exit(0);
            }
            if (event.type == sfEvtTextEntered) {
                if (event.text.unicode == '\r' || event.text.unicode == '\n')
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
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEnter)
                nameEntered = true;
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
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        sfRenderWindow_drawRectangleShape(window, button, NULL);
        sfRenderWindow_drawText(window, nameText, NULL);
        sfRenderWindow_drawText(window, buttonText, NULL);
        sfRenderWindow_display(window);
    }
    strncpy(player->playerName, name, MAX_NAME_LENGTH);
    if (strlen(player->playerName) == 0)
        strncpy(player->playerName, "Guest", MAX_NAME_LENGTH);
    sfText_destroy(nameText);
    sfText_destroy(buttonText);
    sfRectangleShape_destroy(button);
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
}
