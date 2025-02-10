/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** main.c
*/

#include "include/sokoban.h"

int main(void)
{
    GameSettings *settings = init_settings();
    sfVideoMode mode = {WINDOW_WIDTH, WINDOW_HEIGHT, 32};
    sfRenderWindow* window = sfRenderWindow_create(mode, "Sokoban", sfClose, NULL);
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
    int moveCounter = 0;
    sfClock* gameClock = sfClock_create();
    sfMusic* menuMusic = sfMusic_createFromFile("assets/musics/menu.mp3");
    sfMusic* levelMusic = NULL;

    if (!window || !font || !menuMusic || !gameClock)
        return 84;
    srand(time(NULL));
    sfRenderWindow_setFramerateLimit(window, 60);
    if (!font) {
        printf("Failed to load font\n");
        return -1;
    }
    if (menuMusic) {
        sfMusic_setLoop(menuMusic, sfTrue);
        sfMusic_play(menuMusic);
    }
    gamemenudisplay:
    error = displayGameMenu(window, &assets, menuMusic, settings, levelMusic);
    if (error == -1)
        return 0;
    askname:
    if (askPlayerName(window, font, &player) == -1)
        goto gamemenudisplay;
    loadScore(&player);
    player.difficulty = selectDifficulty(window, font);
    if (player.difficulty == -1)
        goto askname;
    assets = loadAssets(player.difficulty, window);
    if (menuMusic) {
        sfMusic_stop(menuMusic);
    }
    levelMusic = assets.levelMusic;
    if (levelMusic) {
        sfMusic_setLoop(levelMusic, sfTrue);
        sfMusic_play(levelMusic);
    }
    apply_sound_settings(settings, menuMusic, levelMusic);
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
    level = generateLevel(minBoxes, maxBoxes, numPokemons, player.difficulty);
    level->difficulty = player.difficulty;
    sfClock_restart(gameClock);
    moveCounter = 0;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
            if (event.type == sfEvtResized) {
                view = sfView_createFromRect((sfFloatRect){0, 0, event.size.width, event.size.height});
                if (!view)
                    return 84;
                sfRenderWindow_setView(window, view);
                sfView_destroy(view);
            }
            if (event.type == sfEvtKeyPressed) {
                switch (event.key.code) {
                    case sfKeyZ:
                        assets = movePlayer(level, 0, -1, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyS:
                        assets = movePlayer(level, 0, 1, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyQ:
                        assets = movePlayer(level, -1, 0, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyD:
                        assets = movePlayer(level, 1, 0, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyUp:
                        assets = movePlayer(level, 0, -1, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyDown:
                        assets = movePlayer(level, 0, 1, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyLeft:
                        assets = movePlayer(level, -1, 0, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyRight:
                        assets = movePlayer(level, 1, 0, assets, &animationDirection, &moveCounter, settings, window);
                        break;
                    case sfKeyR:
                        freeLevel(level);
                        level = generateLevel(minBoxes, maxBoxes, numPokemons, player.difficulty);
                        moveCounter = 0;
                        sfClock_restart(gameClock);
                        break;
                    case sfKeyEscape:
                        displayPauseMenu(window, font, &player, &level, &minBoxes, &maxBoxes, &assets, &numPokemons, menuMusic, settings);
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
                    displayWinMenu(window, font, &player, &level, &minBoxes, &maxBoxes, &assets, &numPokemons, menuMusic);
                    sfClock_restart(gameClock);
                    moveCounter = 0;
                }
            }
        }
        sfRenderWindow_clear(window, sfBlack);
        renderLevel(window, level, assets, numPokemons, animationDirection, settings, font, moveCounter, gameClock);
        sfRenderWindow_display(window);
    }
    freeLevel(level);
    freeAssets(assets);
    sfFont_destroy(font);
    sfRenderWindow_destroy(window);
    if (menuMusic) {
        sfMusic_destroy(menuMusic);
        menuMusic = NULL;
    }
    sfClock_destroy(gameClock);
    return 0;
}
