/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** main.c
*/

#include "include/sokoban.h"

int main(void)
{
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Sokoban", sfResize | sfClose, NULL);
    sfView* view;
    sfEvent event;
    Level* level;
    int minBoxes;
    int maxBoxes;
    Player player = {"", 0, 1};
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
    player.difficulty = selectDifficulty(window, font);
    switch (player.difficulty) {
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
                        displayMenu(window, font, &player, &level);
                        switch (player.difficulty) {
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
                        break;
                    default:
                        break;
                }
                if (checkWin(level)) {
                    player.score += 100;
                    displayMenu(window, font, &player, &level);
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