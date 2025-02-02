/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** difficulty.c
*/

#include "../include/sokoban.h"

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

int getNumBoxesForDifficulty(int difficulty)
{
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
