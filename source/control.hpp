#include "controlutils.hpp"

void init() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Controle da Escotilha");

    SetTargetFPS(60);

    Image shard = LoadImage("./assets/dragonshard.png");
    ImageResize(&shard, 100, 100);

    SetWindowIcon(shard);

    textures["shard"] = LoadTextureFromImage(shard);

    UnloadImage(shard);

    buildRelays();
    buildConnectors();
}

void update(Gamestate &state) {

    mousePoint = GetMousePosition();
    InputConnector::OutputConnector target;

    dragLineStartPoint = { 0.0f, 0.0f };
    dragLineEndPoint = { 0.0f, 0.0f };

    switch (state) {

    case closed:
        state = open;
        break;
    
    case open:    

        defaultOn.refreshHookPositions();
        defaultOff.refreshHookPositions();
        powerConnectors();
        defaultOn.powerRelay();
        defaultOff.powerRelay();
        checkButtonPress();
        toggleLights();
        if (clickedInputConnector()) {state = dragging;}
        break;

    case dragging:

        powerConnectors();

        dragLineStartPoint = dragged->hookCenter;
        dragLineEndPoint = mousePoint;

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {

            if (releasedOverOutputConnector()) {
                dragLineEndPoint = dragged->linked->hookCenter;
                powerLines.push_back({dragLineStartPoint, dragLineEndPoint});
            }
            else {
                dragged = nullptr;
            }
            state = open;
        }
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
        drawRelay(defaultOn);
        drawRelay(defaultOff);
        drawCrystals(textures["shard"]);
        drawButtons();

        for (Link l : powerLines) {
            DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, BLUE);
        }
        
        break;

    case dragging:
        drawBackground();
        drawOpenPlate();
        drawRelay(defaultOn);
        drawRelay(defaultOff);
        drawCrystals(textures["shard"]);
        drawButtons();
        // Draw Connectors
        for (const auto& [label, connector] : inputs) {
            DrawRectangleLinesEx(connector.hook, 3, WHITE);
        }
        for (const auto& [label, connector] : outputs) {
            DrawRectangleLinesEx(connector.hook, 3, YELLOW);
        }

        // Draw established lines
        for (Link l : powerLines) {
            DrawLine(l.start.x, l.start.y, l.end.x, l.end.y, BLUE);
        }

        // Draw dragline
        DrawLineBezier(dragLineStartPoint, dragLineEndPoint, 5, ORANGE);

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