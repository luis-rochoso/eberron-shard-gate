#include "raylib.h"

void drawBackground() {
    ClearBackground(GRAY);
}

void drawOpenPlate() {

    int plateXStart = GetScreenWidth() / 16;
    int plateYStart = GetScreenHeight() / 10;
    int plateWidth = plateXStart * 14;
    int plateHeight = plateYStart * 8;

    Rectangle plate {plateXStart, plateYStart, plateWidth, plateHeight};

    DrawRectangle(plate.x, plate.y, plate.width, plate.height, BLACK);
    DrawRectangleLinesEx(plate, 10, DARKGRAY);

}