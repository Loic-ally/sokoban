/*
** EPITECH PROJECT, 2025
** settings.c
** File description:
** Every settings related functions
*/

#include "../include/sokoban.h"

GameSettings *init_settings(void)
{
    GameSettings *settings = malloc(sizeof(GameSettings));

    settings->showGridLines = false;
    settings->musicEnabled = true;
    settings->musicVolume = 100;
    settings->soundEffectsEnabled = true;
    settings->soundEffectsVolume = 50;
    settings->showMoveCounter = true;
    settings->showTimer = true;
    settings->showPushCounter = true;
    settings->showFps = false;
    return settings;
}

static void drawSlider(sfRenderWindow* window, sfFont* font, const char* label, 
    int* value, sfVector2f position)
{
    sfText* text = sfText_create();
    sfRectangleShape* slider = sfRectangleShape_create();
    sfRectangleShape* handle = sfRectangleShape_create();
    sfVector2f mousePos;
    char valueStr[10];
    
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setColor(text, sfBlack);
    sfText_setString(text, label);
    sfText_setPosition(text, position);
    sfRenderWindow_drawText(window, text, NULL);
    sfRectangleShape_setSize(slider, (sfVector2f){200, 10});
    sfRectangleShape_setPosition(slider, (sfVector2f){position.x + 250, position.y + 10});
    sfRectangleShape_setFillColor(slider, sfColor_fromRGB(200, 200, 200));
    sfRenderWindow_drawRectangleShape(window, slider, NULL);
    sfRectangleShape_setSize(handle, (sfVector2f){20, 20});
    sfRectangleShape_setPosition(handle, 
        (sfVector2f){position.x + 250 + (*value * 180 / 100), position.y + 5});
    sfRectangleShape_setFillColor(handle, sfBlue);
    sfRenderWindow_drawRectangleShape(window, handle, NULL);
    sprintf(valueStr, "%d%%", *value);
    sfText_setString(text, valueStr);
    sfText_setPosition(text, (sfVector2f){position.x + 470, position.y});
    sfRenderWindow_drawText(window, text, NULL);
    
    sfText_destroy(text);
    sfRectangleShape_destroy(slider);
    sfRectangleShape_destroy(handle);
}

static void drawToggle(sfRenderWindow* window, sfFont* font, const char* label, 
    bool* value, sfVector2f position)
{
    sfText* text = sfText_create();
    sfRectangleShape* toggle = sfRectangleShape_create();
    sfText* toggleText = sfText_create();
    
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 24);
    sfText_setColor(text, sfBlack);
    sfText_setString(text, label);
    sfText_setPosition(text, position);
    sfRenderWindow_drawText(window, text, NULL);

    sfRectangleShape_setSize(toggle, (sfVector2f){60, 30});
    sfRectangleShape_setPosition(toggle, (sfVector2f){position.x + 350, position.y});
    sfRectangleShape_setOutlineThickness(toggle, 2);
    sfRectangleShape_setFillColor(toggle, sfTransparent);
    if (*value) {
        sfRectangleShape_setOutlineColor(toggle, sfGreen);
        sfText_setString(toggleText, "o");
    } else {
        sfRectangleShape_setOutlineColor(toggle, sfRed);
        sfText_setString(toggleText, "x");
    }
    sfRenderWindow_drawRectangleShape(window, toggle, NULL);

    sfText_setFont(toggleText, font);
    sfText_setCharacterSize(toggleText, 24);
    sfText_setColor(toggleText, sfBlack);
    sfText_setPosition(toggleText, (sfVector2f){position.x + 370, position.y - 3});
    sfRenderWindow_drawText(window, toggleText, NULL);

    sfText_destroy(text);
    sfRectangleShape_destroy(toggle);
    sfText_destroy(toggleText);
}

static void handleSliderClick(sfVector2f mousePos, sfVector2f position, int* value)
{
    if (mousePos.y >= position.y && mousePos.y <= position.y + 30) {
        if (mousePos.x >= position.x + 250 && mousePos.x <= position.x + 450) {
            *value = ((mousePos.x - (position.x + 250)) / 180.0f) * 100;
            if (*value < 0) *value = 0;
            if (*value > 100) *value = 100;
        }
    }
}

static void handleToggleClick(sfVector2f mousePos, sfVector2f position, bool* value)
{
    if (mousePos.y >= position.y && mousePos.y <= position.y + 30) {
        if (mousePos.x >= position.x + 250 && mousePos.x <= position.x + 310) {
            *value = !*value;
        }
    }
}

void apply_brightness(sfRenderWindow* window, float brightness) {
    sfColor color = sfColor_fromRGB(
        (sfUint8)(255 * brightness),
        (sfUint8)(255 * brightness),
        (sfUint8)(255 * brightness)
    );
    sfRenderWindow_clear(window, color);
}

void apply_sound_settings(GameSettings* game_set, sfMusic* menuMusic, sfMusic* levelMusic)
{
    if (game_set->musicEnabled) {
        sfMusic_setVolume(menuMusic, game_set->musicVolume);
        if (levelMusic) {
            sfMusic_setVolume(levelMusic, game_set->musicVolume);
        }
    } else {
        sfMusic_setVolume(menuMusic, 0);
        if (levelMusic) {
            sfMusic_setVolume(levelMusic, 0);
        }
    }
}

int settings(sfRenderWindow* window, GameSettings* game_set, sfMusic* menuMusic, sfMusic* levelMusic)
{
    sfEvent event;
    sfFont* font = sfFont_createFromFile("assets/font.ttf");
    sfTexture* backgroundTexture = sfTexture_createFromFile("assets/menu/menu_settings.png", NULL);
    sfSprite* backgroundSprite = sfSprite_create();
    sfRectangleShape* saveButton = sfRectangleShape_create();
    sfText* saveText = sfText_create();
    bool isOpen = true;
    sfVector2f mousePos;

    if (!font || !backgroundTexture) {
        printf("Failed to load assets\n");
        return -1;
    }
    sfSprite_setTexture(backgroundSprite, backgroundTexture, sfTrue);
    sfRectangleShape_setSize(saveButton, (sfVector2f){200, 50});
    sfRectangleShape_setPosition(saveButton, (sfVector2f){(1920 / 2) - 100, 900});
    sfRectangleShape_setFillColor(saveButton, sfGreen);
    sfText_setFont(saveText, font);
    sfText_setString(saveText, "Save Settings");
    sfText_setCharacterSize(saveText, 20);
    sfText_setColor(saveText, sfWhite);
    sfText_setPosition(saveText, (sfVector2f){870, 910});

    while (isOpen && sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed) {
                sfRenderWindow_close(window);
                sfRenderWindow_destroy(window);
                exit(0);
                isOpen = false;
            }
            if (event.type == sfEvtMouseButtonPressed) {
                mousePos = (sfVector2f){event.mouseButton.x, event.mouseButton.y};

                handleSliderClick(mousePos, (sfVector2f){700, 300}, &game_set->musicVolume);
                handleSliderClick(mousePos, (sfVector2f){700, 400}, &game_set->soundEffectsVolume);

                handleToggleClick(mousePos, (sfVector2f){800, 500}, &game_set->showGridLines);
                handleToggleClick(mousePos, (sfVector2f){800, 550}, &game_set->musicEnabled);
                handleToggleClick(mousePos, (sfVector2f){800, 600}, &game_set->soundEffectsEnabled);
                handleToggleClick(mousePos, (sfVector2f){800, 650}, &game_set->showMoveCounter);
                handleToggleClick(mousePos, (sfVector2f){800, 700}, &game_set->showTimer);
                handleToggleClick(mousePos, (sfVector2f){800, 750}, &game_set->showFps);
                handleToggleClick(mousePos, (sfVector2f){800, 800}, &game_set->showPushCounter);

                sfFloatRect buttonBounds = sfRectangleShape_getGlobalBounds(saveButton);
                if (sfFloatRect_contains(&buttonBounds, mousePos.x, mousePos.y)) {
                    isOpen = false;
                }
            }
            if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape) {
                isOpen = false;
            }
        }

        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, backgroundSprite, NULL);
        drawSlider(window, font, "Music Volume", &game_set->musicVolume, (sfVector2f){700, 300});
        drawSlider(window, font, "Sound Effects", &game_set->soundEffectsVolume, (sfVector2f){700, 400});
        drawToggle(window, font, "Show Grid Lines", &game_set->showGridLines, (sfVector2f){700, 500});
        drawToggle(window, font, "Music Enabled", &game_set->musicEnabled, (sfVector2f){700, 550});
        drawToggle(window, font, "Sound Effects", &game_set->soundEffectsEnabled, (sfVector2f){700, 600});
        drawToggle(window, font, "Show Move Counter", &game_set->showMoveCounter, (sfVector2f){700, 650});
        drawToggle(window, font, "Show Timer", &game_set->showTimer, (sfVector2f){700, 700});
        drawToggle(window, font, "Show FPS", &game_set->showFps, (sfVector2f){700, 750});
        drawToggle(window, font, "Show Push Counter", &game_set->showPushCounter, (sfVector2f){700, 800});
        sfRenderWindow_drawRectangleShape(window, saveButton, NULL);
        sfRenderWindow_drawText(window, saveText, NULL);
        sfRenderWindow_display(window);
    }
    sfSprite_destroy(backgroundSprite);
    sfTexture_destroy(backgroundTexture);
    sfRectangleShape_destroy(saveButton);
    sfText_destroy(saveText);
    sfFont_destroy(font);

    apply_sound_settings(game_set, menuMusic, levelMusic);
    return 0;
}