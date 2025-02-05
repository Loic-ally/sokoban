/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** main.c
*/

#include "include/sokoban.h"

unsigned int WINDOW_WIDTH;
unsigned int WINDOW_HEIGHT;

static void get_screen_size(void)
{
    sfVideoMode desktopMode = sfVideoMode_getDesktopMode();
    WINDOW_WIDTH = desktopMode.width;
    WINDOW_HEIGHT = desktopMode.height;
}

int main(void)
{
    get_screen_size();
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Sokoban", sfResize | sfClose, NULL);
    sfView* view;
    sfEvent event;
    Level* level = NULL;
    int minBoxes;
    int maxBoxes;
    int numPokemons;
    Player player = {"", 0, 1};
    Assets assets = {0};
    sfFont* font = sfFont_createFromFile("assets/font.ttf");
    int error;
    int animationDirection = 0;

    srand(time(NULL));
    sfRenderWindow_setFramerateLimit(window, 60);
    if (!font) {
        printf("Failed to load font\n");
        return -1;
    }
    error = displayGameMenu(window, &assets);
    if (error == -1)
        return 0;
    
    askPlayerName(window, font, &player);
    loadScore(&player);
    player.difficulty = selectDifficulty(window, font);
    assets = loadAssets(player.difficulty, window);
    switch (player.difficulty) {
        case 1:
            minBoxes = 1;
            maxBoxes = 5;
            numPokemons = 4;
            break;
        case 2:
            minBoxes = 6;
            maxBoxes = 10;
            numPokemons = 5;
            break;
        case 3:
            minBoxes = 11;
            maxBoxes = 15;
            numPokemons = 4;
            break;
        case 4:
            minBoxes = 16;
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
                    case sfKeyZ:
                        assets = movePlayer(level, 0, -1, assets, &animationDirection);
                        break;
                    case sfKeyS:
                        assets = movePlayer(level, 0, 1, assets, &animationDirection);
                        break;
                    case sfKeyQ:
                        assets = movePlayer(level, -1, 0, assets, &animationDirection);
                        break;
                    case sfKeyD:
                        assets = movePlayer(level, 1, 0, assets, &animationDirection);
                        break;
                    case sfKeyR:
                        freeLevel(level);
                        level = generateLevel(minBoxes, maxBoxes, numPokemons);
                        break;
                    case sfKeyEscape:
                        displayMenu(window, font, &player, &level, &minBoxes, &maxBoxes, &assets, &numPokemons);
                        break;
                    default:
                        break;
                }
                if (checkWin(level)) {
                    switch (player.difficulty) {
                        case 1:
                            player.score += 100;
                            break;
                        case 2:
                            player.score += 250;
                            break;
                        case 3:
                            player.score += 500;
                            break;
                        case 4:
                            player.score += 1000;
                            break;
                        default:
                            player.score += 100;
                            break;
                    }
                    saveScore(player);
                    displayMenu(window, font, &player, &level, &minBoxes, &maxBoxes, &assets, &numPokemons);
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        renderLevel(window, level, assets, numPokemons, animationDirection);
        sfRenderWindow_display(window);
    }
    freeLevel(level);
    freeAssets(assets);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);
    return 0;
}
