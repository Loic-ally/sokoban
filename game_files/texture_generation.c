/*
** EPITECH PROJECT, 2024
** sokoban
** File description:
** texture_generation.c
*/

#include "../include/sokoban.h"

Assets loadAssets()
{
    Assets assets;
    float scale = (float)TILE_SIZE / SPRITE_SIZE;
    sfTexture* playerTexture = sfTexture_createFromFile("assets/player.png", NULL);
    sfTexture* wallTexture = sfTexture_createFromFile("assets/wall.png", NULL);
    sfTexture* boxTexture = sfTexture_createFromFile("assets/box.png", NULL);
    sfTexture* targetTexture = sfTexture_createFromFile("assets/storage.png", NULL);
    sfTexture* floorTexture = sfTexture_createFromFile("assets/floor.png", NULL);
    sfVector2f spriteScale = {scale, scale};

    assets.playerSprite = sfSprite_create();
    assets.wallSprite = sfSprite_create();
    assets.boxSprite = sfSprite_create();
    assets.targetSprite = sfSprite_create();
    assets.floorSprite = sfSprite_create();
    
    sfSprite_setTexture(assets.playerSprite, playerTexture, sfTrue);
    sfSprite_setTexture(assets.wallSprite, wallTexture, sfTrue);
    sfSprite_setTexture(assets.boxSprite, boxTexture, sfTrue);
    sfSprite_setTexture(assets.targetSprite, targetTexture, sfTrue);
    sfSprite_setTexture(assets.floorSprite, floorTexture, sfTrue);
    
    sfSprite_setScale(assets.playerSprite, spriteScale);
    sfSprite_setScale(assets.wallSprite, spriteScale);
    sfSprite_setScale(assets.boxSprite, spriteScale);
    sfSprite_setScale(assets.targetSprite, spriteScale);
    sfSprite_setScale(assets.floorSprite, spriteScale);
    
    return assets;
}
