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
    int numPokemons;
    Player player = {"", 0, 1};
    Assets assets;
    sfFont* font = sfFont_createFromFile("assets/font.ttf");

    srand(time(NULL));
    sfRenderWindow_setFramerateLimit(window, 60);
    if (!font) {
        printf("Failed to load font\n");
        return -1;
    }
    askPlayerName(window, font, &player);
    loadScore(&player);
    player.difficulty = selectDifficulty(window, font);
    assets = loadAssets(player.difficulty);
    switch (player.difficulty) {
        case 1:
            minBoxes = 1;
            maxBoxes = 5;
            numPokemons = 4;
            break;
        case 2:
            minBoxes = 5;
            maxBoxes = 10;
            numPokemons = 5;
            break;
        case 3:
            minBoxes = 10;
            maxBoxes = 15;
            numPokemons = 4;
            break;
        case 4:
            minBoxes = 15;
            maxBoxes = 20;
            numPokemons = 3;
            break;
        default:
            minBoxes = 1;
            maxBoxes = 5;
            numPokemons = 4;
            break;
    }
    level = generateLevel(minBoxes, maxBoxes, numPokemons);
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
                        level = generateLevel(minBoxes, maxBoxes, numPokemons);
                        break;
                    case sfKeyEscape:
                        displayMenu(window, font, &player, &level, &minBoxes, &maxBoxes, &assets, &numPokemons);
                        break;
                    case sfKeyQ:
                        sfRenderWindow_close(window);
                        break;
                    default:
                        break;
                }
                if (checkWin(level)) {
                    player.score += 100;
                    saveScore(player);
                    displayMenu(window, font, &player, &level, &minBoxes, &maxBoxes, &assets, &numPokemons);
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        renderLevel(window, level, assets, numPokemons);
        sfRenderWindow_display(window);
    }
    freeLevel(level);
    freeAssets(assets);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);
    return 0;
}