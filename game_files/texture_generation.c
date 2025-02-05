/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** texture_generation.c
*/

#include "../include/sokoban.h"

Assets loadAssets(int difficulty, sfRenderWindow* window)
{
    Assets assets;
    float scale = (float)TILE_SIZE / SPRITE_SIZE;
    sfTexture* playerTexture = customCharacter(window, assets);
    sfTexture* boxTexture;
    sfTexture* targetTexture;
    sfTexture* floorTexture;
    sfTexture* wallTexture;
    sfTexture* backgroundTexture;
    sfTexture* pokemonTextures[6] = {NULL, NULL, NULL, NULL, NULL, NULL};
    sfVector2f spriteScale = {scale, scale};
    sfIntRect rect = {0, 0, 50, 50};

    assets.backgroundSprite = sfSprite_create();
    assets.boxSprite = sfSprite_create();
    assets.targetSprite = sfSprite_create();
    assets.floorSprite = sfSprite_create();
    assets.wallSprite = sfSprite_create();
    assets.playerSprite = sfSprite_create();

    switch (difficulty) {
        case 1:
            boxTexture = sfTexture_createFromFile("assets/decorations/easy/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/easy/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/easy/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/easy/background.png", NULL);
            pokemonTextures[0] = sfTexture_createFromFile("assets/decorations/easy/pokemon0.png", NULL);
            pokemonTextures[1] = sfTexture_createFromFile("assets/decorations/easy/pokemon1.png", NULL);
            pokemonTextures[2] = sfTexture_createFromFile("assets/decorations/easy/pokemon2.png", NULL);
            pokemonTextures[3] = sfTexture_createFromFile("assets/decorations/easy/pokemon3.png", NULL);
            wallTexture = sfTexture_createFromFile("assets/decorations/easy/walls_easy.png", NULL);
            break;
        case 2:
            boxTexture = sfTexture_createFromFile("assets/decorations/normal/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/normal/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/normal/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/normal/background.png", NULL);
            pokemonTextures[0] = sfTexture_createFromFile("assets/decorations/normal/pokemon0.png", NULL);
            pokemonTextures[1] = sfTexture_createFromFile("assets/decorations/normal/pokemon1.png", NULL);
            pokemonTextures[2] = sfTexture_createFromFile("assets/decorations/normal/pokemon2.png", NULL);
            pokemonTextures[3] = sfTexture_createFromFile("assets/decorations/normal/pokemon3.png", NULL);
            pokemonTextures[4] = sfTexture_createFromFile("assets/decorations/normal/pokemon4.png", NULL);
            wallTexture = sfTexture_createFromFile("assets/decorations/normal/walls_normal.png", NULL);
            break;
        case 3:
            boxTexture = sfTexture_createFromFile("assets/decorations/hard/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/hard/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/hard/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/hard/background.png", NULL);
            pokemonTextures[0] = sfTexture_createFromFile("assets/decorations/hard/pokemon0.png", NULL);
            pokemonTextures[1] = sfTexture_createFromFile("assets/decorations/hard/pokemon1.png", NULL);
            pokemonTextures[2] = sfTexture_createFromFile("assets/decorations/hard/pokemon2.png", NULL);
            pokemonTextures[3] = sfTexture_createFromFile("assets/decorations/hard/pokemon3.png", NULL);
            wallTexture = sfTexture_createFromFile("assets/decorations/hard/walls_hard.png", NULL);
            break;
        case 4:
            boxTexture = sfTexture_createFromFile("assets/decorations/hell/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/hell/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/hell/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/hell/background.png", NULL);
            pokemonTextures[0] = sfTexture_createFromFile("assets/decorations/hell/pokemon0.png", NULL);
            pokemonTextures[1] = sfTexture_createFromFile("assets/decorations/hell/pokemon1.png", NULL);
            pokemonTextures[2] = sfTexture_createFromFile("assets/decorations/hell/pokemon2.png", NULL);
            wallTexture = sfTexture_createFromFile("assets/decorations/hell/walls_hell.png", NULL);
            break;
        default:
            boxTexture = sfTexture_createFromFile("assets/decorations/easy/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/easy/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/easy/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/easy/background.png", NULL);
            pokemonTextures[0] = sfTexture_createFromFile("assets/decorations/easy/pokemon0.png", NULL);
            pokemonTextures[1] = sfTexture_createFromFile("assets/decorations/easy/pokemon1.png", NULL);
            pokemonTextures[2] = sfTexture_createFromFile("assets/decorations/easy/pokemon2.png", NULL);
            pokemonTextures[3] = sfTexture_createFromFile("assets/decorations/easy/pokemon3.png", NULL);
            wallTexture = sfTexture_createFromFile("assets/decorations/easy/walls_easy.png", NULL);
            break;
    }

    for (int i = 0; i < 6; i++) {
        if (pokemonTextures[i]) {
            assets.pokemonSprites[i] = sfSprite_create();
            sfSprite_setTexture(assets.pokemonSprites[i], pokemonTextures[i], sfTrue);
            sfSprite_setScale(assets.pokemonSprites[i], spriteScale);
            assets.pokemonTextures[i] = pokemonTextures[i];
        } else {
            assets.pokemonSprites[i] = NULL;
            assets.pokemonTextures[i] = NULL;
        }
    }

    switch (difficulty) {
        case 1:
            sfSprite_setPosition(assets.pokemonSprites[0], (sfVector2f){1550, 325});
            sfSprite_setPosition(assets.pokemonSprites[1], (sfVector2f){745, 1000});
            sfSprite_setPosition(assets.pokemonSprites[2], (sfVector2f){210, 745});
            sfSprite_setPosition(assets.pokemonSprites[3], (sfVector2f){180, 50});
            break;
        case 2:
            sfSprite_setPosition(assets.pokemonSprites[0], (sfVector2f){220, 90});
            sfSprite_setPosition(assets.pokemonSprites[1], (sfVector2f){800, 0});
            sfSprite_setPosition(assets.pokemonSprites[2], (sfVector2f){1525, 10});
            sfSprite_setPosition(assets.pokemonSprites[3], (sfVector2f){750, 980});
            sfSprite_setPosition(assets.pokemonSprites[4], (sfVector2f){1750, 50});
            break;
        case 3:
            sfSprite_setPosition(assets.pokemonSprites[0], (sfVector2f){670, 0});
            sfSprite_setPosition(assets.pokemonSprites[1], (sfVector2f){1400, 605});
            sfSprite_setPosition(assets.pokemonSprites[2], (sfVector2f){265, 645});
            sfSprite_setPosition(assets.pokemonSprites[3], (sfVector2f){1230, 985});
            break;
        case 4:
            sfSprite_setPosition(assets.pokemonSprites[0], (sfVector2f){395, 920});
            sfSprite_setPosition(assets.pokemonSprites[1], (sfVector2f){590, 0});
            sfSprite_setPosition(assets.pokemonSprites[2], (sfVector2f){1470, 260});
            break;
        default:
            
            break;
    }

    sfSprite_setTexture(assets.wallSprite, wallTexture, sfTrue);
    sfSprite_setTexture(assets.backgroundSprite, backgroundTexture, sfTrue);
    sfSprite_setTexture(assets.boxSprite, boxTexture, sfTrue);
    sfSprite_setTexture(assets.targetSprite, targetTexture, sfTrue);
    sfSprite_setTexture(assets.floorSprite, floorTexture, sfTrue);
    sfSprite_setTexture(assets.playerSprite, playerTexture, sfTrue);

    sfSprite_setTextureRect(assets.playerSprite, rect);

    sfSprite_setScale(assets.boxSprite, spriteScale);
    sfSprite_setScale(assets.targetSprite, spriteScale);
    sfSprite_setScale(assets.floorSprite, spriteScale);
    sfSprite_setScale(assets.wallSprite, spriteScale);

    return assets;
}
