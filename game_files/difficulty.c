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
    sfText* buttonText1 = sfText_create();
    sfText* buttonText2 = sfText_create();
    sfText* buttonText3 = sfText_create();
    sfText* buttonText4 = sfText_create();
    int difficulty = 0;
    bool difficultySelected = false;
    sfEvent event;
    sfFloatRect button1Bounds;
    sfFloatRect button2Bounds;
    sfFloatRect button3Bounds;
    sfFloatRect button4Bounds;
    sfTexture* backgroundTexture = sfTexture_createFromFile("assets/menu/menu_difficulty.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();

    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
    sfText_setFont(buttonText1, font);
    sfText_setCharacterSize(buttonText1, 50);
    sfText_setColor(buttonText1, sfBlack);
    sfText_setString(buttonText1, "Easy");
    sfText_setPosition(buttonText1, (sfVector2f){WINDOW_WIDTH / 4 + 115, WINDOW_HEIGHT / 4 + 125});

    sfText_setFont(buttonText2, font);
    sfText_setCharacterSize(buttonText2, 50);
    sfText_setColor(buttonText2, sfBlack);
    sfText_setString(buttonText2, "Normal");
    sfText_setPosition(buttonText2, (sfVector2f){WINDOW_WIDTH / 4 + 575, WINDOW_HEIGHT / 4 + 125});

    sfText_setFont(buttonText3, font);
    sfText_setCharacterSize(buttonText3, 50);
    sfText_setColor(buttonText3, sfBlack);
    sfText_setString(buttonText3, "Hard");
    sfText_setPosition(buttonText3, (sfVector2f){WINDOW_WIDTH / 4 + 115, WINDOW_HEIGHT / 4 + 350});

    sfText_setFont(buttonText4, font);
    sfText_setCharacterSize(buttonText4, 50);
    sfText_setColor(buttonText4, sfBlack);
    sfText_setString(buttonText4, "Hell");
    sfText_setPosition(buttonText4, (sfVector2f){WINDOW_WIDTH / 4 + 620, WINDOW_HEIGHT / 4 + 350});

    while (!difficultySelected) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                difficultySelected = true;
                exit(0);
            }
            if (event.type == sfEvtMouseButtonPressed) {
                if (event.mouseButton.button == sfMouseLeft) {
                    mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};
                    button1Bounds = sfText_getGlobalBounds(buttonText1);
                    button2Bounds = sfText_getGlobalBounds(buttonText2);
                    button3Bounds = sfText_getGlobalBounds(buttonText3);
                    button4Bounds = sfText_getGlobalBounds(buttonText4);
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
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        sfRenderWindow_drawText(window, buttonText1, NULL);
        sfRenderWindow_drawText(window, buttonText2, NULL);
        sfRenderWindow_drawText(window, buttonText3, NULL);
        sfRenderWindow_drawText(window, buttonText4, NULL);
        sfRenderWindow_display(window);
    }

    sfText_destroy(buttonText1);
    sfText_destroy(buttonText2);
    sfText_destroy(buttonText3);
    sfText_destroy(buttonText4);
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
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
