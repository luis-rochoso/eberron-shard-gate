#include "states.hpp"
#include "interface.hpp"

void init() {
    static const int SCREEN_WIDTH = 800;
    static const int SCREEN_HEIGHT = 450;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Controle da Escotilha");

    SetTargetFPS(60);
}

void update(Gamestate &state) {

    switch (state)
    {
    case closed:
        state = open;
        break;
    
    case open:
        
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
        break;

    case dragging:
        break;
    
    default:
        break;
    }
    EndDrawing();
}