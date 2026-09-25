#include "control.hpp"

int main() {
    Gamestate state {closed};

    while ((state != end) or !WindowShouldClose()) {
        update(state);
        render(state);
    }

    return 0;
}