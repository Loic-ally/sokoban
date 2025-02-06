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
    sfRectangleShape* buttons[10];
    sfText* buttonTexts[10];
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
    char buttonText[3];

    for (int i = 0; i < 10; i++) {
        characterTextures[i] = sfTexture_createFromFile(characterFiles[i], NULL);
        characterSprites[i] = sfSprite_create();
        sfSprite_setTexture(characterSprites[i], characterTextures[i], sfTrue);
        sfSprite_setTextureRect(characterSprites[i], rect);
        sfSprite_setScale(characterSprites[i], (sfVector2f){4.0f, 4.0f});

        buttons[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(buttons[i], (sfVector2f){200, 50});
        sfRectangleShape_setOutlineColor(buttons[i], sfBlack);
        sfRectangleShape_setOutlineThickness(buttons[i], 2);
        sfRectangleShape_setFillColor(buttons[i], sfTransparent);

        buttonTexts[i] = sfText_create();
        sfText_setFont(buttonTexts[i], font);
        sprintf(buttonText, "%d", i + 1);
        sfText_setString(buttonTexts[i], buttonText);
        sfText_setCharacterSize(buttonTexts[i], 24);
        sfText_setColor(buttonTexts[i], sfBlack);
    }

    for (int i = 0; i < 10; i++) {
        sfSprite_setPosition(characterSprites[i], (sfVector2f){100 + (i % 5) * 350, 200 + (i / 5) * 400});
        sfRectangleShape_setPosition(buttons[i], (sfVector2f){100 + (i % 5) * 350, 400 + (i / 5) * 400});
        sfText_setPosition(buttonTexts[i], (sfVector2f){150 + (i % 5) * 350, 410 + (i / 5) * 400});
    }

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
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    for (int i = 0; i < 10; i++) {
                        buttonBounds = sfRectangleShape_getGlobalBounds(buttons[i]);
                        if (sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y)) {
                            return characterTextures[i];
                        }
                    }
                }
            }
        }
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawText(window, titleText, NULL);
        for (int i = 0; i < 10; i++) {
            sfRenderWindow_drawSprite(window, characterSprites[i], NULL);
            sfRenderWindow_drawRectangleShape(window, buttons[i], NULL);
            sfRenderWindow_drawText(window, buttonTexts[i], NULL);
        }
        sfRenderWindow_display(window);
    }
    return NULL;
}

int displayGameMenu(sfRenderWindow *window, Assets *assets, sfMusic* menuMusic, GameSettings* game_set)
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

    if (!texture) {
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
                        settings(window, game_set);
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

void displayMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level, int* minBoxes, int* maxBoxes, Assets* assets, int* numPokemons, sfMusic* menuMusic)
{
    sfVector2f mousePos;
    sfText* promptText = sfText_create();
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

    if (menuMusic) {
        sfMusic_play(menuMusic);
    }

    sfText_setFont(promptText, font);
    sfText_setCharacterSize(promptText, 24);
    sfText_setColor(promptText, sfBlack);
    sfText_setString(promptText, "Level Complete!\n1. Play again ?\n2. Quit\n3. Change Difficulty");
    sfText_setPosition(promptText, (sfVector2f){WINDOW_WIDTH / 2 + 50, WINDOW_HEIGHT / 4});
    sfRectangleShape_setSize(button1, (sfVector2f){200, 40});
    sfRectangleShape_setFillColor(button1, sfGreen);
    sfRectangleShape_setPosition(button1, (sfVector2f){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 100});
    sfText_setFont(buttonText1, font);
    sfText_setCharacterSize(buttonText1, 24);
    sfText_setColor(buttonText1, sfBlack);
    sfText_setString(buttonText1, "Play Again ?");
    sfText_setPosition(buttonText1, (sfVector2f){WINDOW_WIDTH / 2 + 40, WINDOW_HEIGHT / 4 + 105});
    sfRectangleShape_setSize(button2, (sfVector2f){200, 40});
    sfRectangleShape_setFillColor(button2, sfGreen);
    sfRectangleShape_setPosition(button2, (sfVector2f){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 150});
    sfText_setFont(buttonText2, font);
    sfText_setCharacterSize(buttonText2, 24);
    sfText_setColor(buttonText2, sfBlack);
    sfText_setString(buttonText2, "Change Difficulty");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 155});
    sfRectangleShape_setSize(button3, (sfVector2f){200, 40});
    sfRectangleShape_setFillColor(button3, sfGreen);
    sfRectangleShape_setPosition(button3, (sfVector2f){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 + 200});
    sfText_setFont(buttonText3, font);
    sfText_setCharacterSize(buttonText3, 24);
    sfText_setColor(buttonText3, sfBlack);
    sfText_setString(buttonText3, "Quit");
    sfText_setPosition(buttonText3, (sfVector2f){WINDOW_WIDTH / 2 + 70, WINDOW_HEIGHT / 4 + 205});
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

                        if (assets->levelMusic) {
                            sfMusic_stop(assets->levelMusic);
                            assets->levelMusic = NULL;
                        }

                        freeAssets(*assets);
                        *assets = loadAssets(player->difficulty, window);

                        if (assets->levelMusic) {
                            sfMusic_setLoop(assets->levelMusic, sfTrue);
                            sfMusic_play(assets->levelMusic);
                        }

                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button3Bounds, mousePos.x, mousePos.y)) {
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
        sfRenderWindow_drawRectangleShape(window, button3, NULL);
        sfRenderWindow_drawText(window, buttonText3, NULL);
        sfRenderWindow_display(window);
    }
    sfText_destroy(promptText);
    sfText_destroy(buttonText1);
    sfText_destroy(buttonText2);
    sfText_destroy(buttonText3);
    sfRectangleShape_destroy(button1);
    sfRectangleShape_destroy(button2);
    sfRectangleShape_destroy(button3);
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