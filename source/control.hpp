#include "states.hpp"
#include "interface.hpp"

void render(Gamestate &state) {

    switch (state)
    {
    case closed:
        return;
        break;

    case open:
        break;

    case dragging:
        break;
    
    default:
        return;
        break;
    }

}

void update(Gamestate &state) {

    switch (state)
    {
    case closed:
        return;
        break;
    
    case open:
        break;

    case dragging:
        break;
    
    default:
        return;
        break;
    }

}