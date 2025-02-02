/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** menus.c
*/

#include "../include/sokoban.h"

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

void displayMenu(sfRenderWindow* window, sfFont* font, Player* player, Level** level)
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

    sfText_setFont(promptText, font);
    sfText_setCharacterSize(promptText, 24);
    sfText_setColor(promptText, sfBlack);
    sfText_setString(promptText, "Level Complete!\n1. Play again ?\n2. Quit\n3. Change Difficulty");
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
    sfText_setString(buttonText2, "Change Difficulty");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 155});

    sfRectangleShape_setSize(button3, (sfVector2f){200, 40});
    sfRectangleShape_setFillColor(button3, sfGreen);
    sfRectangleShape_setPosition(button3, (sfVector2f){WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4 + 200});

    sfText_setFont(buttonText3, font);
    sfText_setCharacterSize(buttonText3, 24);
    sfText_setColor(buttonText3, sfBlack);
    sfText_setString(buttonText3, "Quit");
    sfText_setPosition(buttonText3, (sfVector2f){WINDOW_WIDTH / 4 + 70, WINDOW_HEIGHT / 4 + 205});

    while (menuOpen) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                menuOpen = false;
            }
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) {
                menuOpen = false;
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfRectangleShape_getGlobalBounds(button1);
                    button2Bounds = sfRectangleShape_getGlobalBounds(button2);
                    button3Bounds = sfRectangleShape_getGlobalBounds(button3);
                    if (sfFloatRect_contains(&button1Bounds, mousePos.x, mousePos.y)) {
                        saveScore(*player);
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        int newDifficulty = selectDifficulty(window, font);
                        player->difficulty = newDifficulty;
                        int minBoxes, maxBoxes;
                        switch (player->difficulty) {
                            case 1:
                                minBoxes = 1;
                                maxBoxes = 5;
                                break;
                            case 2:
                                minBoxes = 6;
                                maxBoxes = 10;
                                break;
                            case 3:
                                minBoxes = 11;
                                maxBoxes = 15;
                                break;
                            case 4:
                                minBoxes = 16;
                                maxBoxes = 20;
                                break;
                            default:
                                minBoxes = 1;
                                maxBoxes = 5;
                                break;
                        }
                        freeLevel(*level);
                        *level = generateLevel(minBoxes, maxBoxes);
                        menuOpen = false;
                    } else if (sfFloatRect_contains(&button2Bounds, mousePos.x, mousePos.y)) {
                        sfRenderWindow_close(window);
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