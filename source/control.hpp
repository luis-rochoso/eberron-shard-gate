#include <bits/stdc++.h>
#include <string>
#include "states.hpp"
#include "interface.hpp"

Vector2 mousePoint { 0.0f, 0.0f };

bool shardPower [2] = {false, false};

std::unordered_map<std::string, Texture2D> textures;

void init() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Controle da Escotilha");

    SetTargetFPS(60);

    Image shard = LoadImage("./assets/dragonshard.png");
    ImageResize(&shard, 100, 100);

    SetWindowIcon(shard);

    textures["shard"] = LoadTextureFromImage(shard);

    UnloadImage(shard);
}

void update(Gamestate &state) {

    mousePoint = GetMousePosition();

    switch (state)
    {
    case closed:
        state = open;
        break;
    
    case open:
        // Handling pressing Crystal buttons
        for (int i = 0; i < 2; ++i) {
            if (CheckCollisionPointCircle(mousePoint, shardButtons[i].center, buttonRadius)) {
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                    shardPower[i] = !shardPower[i];
                }
            }    
        }

        // Lighting up or out the toggable shards  
        for (int i = 0; i < 2; ++i) {
            shardLight[i] = shardPower[i];
        }
        break;

    case dragging:
        break;
    
    default:
        break;
    }

}

void render(Gamestate &state) {

    BeginDrawing();
    switch (state)
    {
    case closed:
        break;

    case open:
        drawBackground();
        drawOpenPlate();
        drawCrystals(textures["shard"]);
        drawButtons();
        break;

    case dragging:
        break;
    
    default:
        break;
    }
    EndDrawing();
}

void shutdown() {
    for (auto it : textures) {
        UnloadTexture(it.second);
    }
    CloseWindow();
}