#include "relay.hpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

const float PLATE_X = SCREEN_WIDTH / 16;
const float PLATE_Y = SCREEN_HEIGHT / 10;
const float PLATE_WIDTH = PLATE_X * 14;
const float PLATE_HEIGHT = PLATE_Y * 8;

const float buttonRadius = 25;

struct Circle {
    Vector2 center;
    float radius;
};

// 50 is half the shard texture's height
Vector2 buttonCenter[2] = {{PLATE_X - (PLATE_WIDTH/16), PLATE_Y + 50},
                           {PLATE_X - (PLATE_WIDTH/16), PLATE_Y + (PLATE_HEIGHT/3) + 50}};

Circle shardButtons[2] = {{buttonCenter[0], buttonRadius},
                          {buttonCenter[1], buttonRadius}};

bool shardLight[2] = {false, false};
bool exitLight = false;

void drawBackground() {
    ClearBackground(GRAY);
}

void drawOpenPlate() {

    Rectangle plate {PLATE_X, PLATE_Y, PLATE_WIDTH, PLATE_HEIGHT};

    DrawRectangle(plate.x, plate.y, plate.width, plate.height, BLACK);
    DrawRectangleLinesEx(plate, 10, DARKGRAY);

}

void drawCrystals(Texture2D shard) {

    // Crystal 1 (switchable)
    if (shardLight[0]) {
        DrawTexture(shard, PLATE_X, PLATE_Y, RAYWHITE);
    }
    else {
        DrawTexture(shard, PLATE_X, PLATE_Y, GRAY);
    }

    // Crystal 2 (switchable)
    if (shardLight[1]) {
        DrawTexture(shard, PLATE_X, PLATE_Y + (PLATE_HEIGHT/3), RAYWHITE);
    }
    else {
        DrawTexture(shard, PLATE_X, PLATE_Y + (PLATE_HEIGHT/3), GRAY);
    }

    // Crystal 3 (always on)
    DrawTexture(shard, PLATE_X, PLATE_Y + ((PLATE_HEIGHT/3) * 2), RAYWHITE);

}

void drawButtons() {

    // Button 1
    DrawCircleV(buttonCenter[0], buttonRadius + 3, BLACK);
    DrawCircleV(buttonCenter[0], buttonRadius, shardLight[0] ? GREEN : RED);


    // Button 2
    DrawCircleV(buttonCenter[1], buttonRadius + 3, BLACK);
    DrawCircleV(buttonCenter[1], buttonRadius, shardLight[1] ? GREEN : RED);

    // Output signal
    DrawCircle(PLATE_WIDTH + 75, buttonCenter[1].y, buttonRadius / 2, exitLight ? GREEN : RED);
}

void drawRelay(Relay relay) {

    Rectangle mainframe = {relay.origin.x, relay.origin.y, RELAY_WIDTH, RELAY_HEIGHT};

    DrawRectangleRec(mainframe, GRAY);
    DrawRectangleLinesEx(mainframe, 3, WHITE);
}