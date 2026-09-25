#include "control.hpp"

int main() {
    Gamestate state {closed};

    while (true) {
        render();
        update();
    }

    return 0;
}