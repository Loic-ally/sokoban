/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** texture_generation.c
*/

#include "../include/sokoban.h"

Assets loadAssets(int difficulty)
{
    Assets assets;
    float scale = (float)TILE_SIZE / SPRITE_SIZE;
    sfTexture* playerTexture = sfTexture_createFromFile("assets/player.png", NULL);
    sfTexture* boxTexture;
    sfTexture* targetTexture;
    sfTexture* floorTexture;
    sfTexture* wallTexture;
    sfVector2f spriteScale = {scale, scale};
    sfTexture* backgroundTexture;

    switch (difficulty) {
        case 1:
            wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
            boxTexture = sfTexture_createFromFile("assets/decorations/easy/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/easy/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/easy/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/easy/background.png", NULL);
            break;
        case 2:
            wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
            boxTexture = sfTexture_createFromFile("assets/decorations/normal/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/normal/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/normal/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/normal/background.png", NULL);
            break;
        case 3:
            wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
            boxTexture = sfTexture_createFromFile("assets/decorations/hard/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/hard/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/hard/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/hard/background.png", NULL);
            break;
        case 4:
            wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
            boxTexture = sfTexture_createFromFile("assets/decorations/hell/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/decorations/hell/stockage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/decorations/hell/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/hell/background.png", NULL);
            break;
        default:
            wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
            boxTexture = sfTexture_createFromFile("assets/box.png", NULL);
            targetTexture = sfTexture_createFromFile("assets/storage.png", NULL);
            floorTexture = sfTexture_createFromFile("assets/floor.png", NULL);
            backgroundTexture = sfTexture_createFromFile("assets/decorations/easy/background.png", NULL);
            break;
    }

    assets.playerSprite = sfSprite_create();
    assets.backgroundSprite = sfSprite_create();
    assets.boxSprite = sfSprite_create();
    assets.targetSprite = sfSprite_create();
    assets.floorSprite = sfSprite_create();
    assets.wallSprite = sfSprite_create();

    sfSprite_setTexture(assets.wallSprite, wallTexture, sfTrue);
    sfSprite_setTexture(assets.playerSprite, playerTexture, sfTrue);
    sfSprite_setTexture(assets.backgroundSprite, backgroundTexture, sfTrue);
    sfSprite_setTexture(assets.boxSprite, boxTexture, sfTrue);
    sfSprite_setTexture(assets.targetSprite, targetTexture, sfTrue);
    sfSprite_setTexture(assets.floorSprite, floorTexture, sfTrue);

    sfSprite_setScale(assets.playerSprite, spriteScale);
    sfSprite_setScale(assets.boxSprite, spriteScale);
    sfSprite_setScale(assets.targetSprite, spriteScale);
    sfSprite_setScale(assets.floorSprite, spriteScale);
    sfSprite_setScale(assets.wallSprite, spriteScale);

    return assets;
}
