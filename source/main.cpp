#include "control.hpp"

int main() {

    init();

    Gamestate state {closed};

    while ((state != end) and !WindowShouldClose()) {
        update(state);
        render(state);
    }

    CloseWindow();

    return 0;
}