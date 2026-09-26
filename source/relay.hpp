#ifndef RELAY_HPP
#define RELAY_HPP

#include "raylib.h"
#include "connectors.hpp"

const float RELAY_WIDTH = 150;
const float RELAY_HEIGHT = 100;

struct Relay {

    InputConnector* control;
    InputConnector* input;
    InputConnector::OutputConnector* output;

    bool defaultMode;

    void powerRelay() {
        if (defaultMode == true) {
            output->isPowered = !control->isPowered and input->isPowered;
        }
        else {
            output->isPowered = control->isPowered and input->isPowered;
        }
    }

    // Position
    Vector2 origin {0, 0};
    Vector2 getCenter() {
        return {origin.x + RELAY_WIDTH / 2, origin.y + RELAY_HEIGHT};
    }

    void refreshHookPositions() {
        control->hook = {origin.x - 10, origin.y + 25, 25, 25};
        control->hookCenter = {control->hook.x + (control->hook.width / 2),
                               control->hook.y + (control->hook.height / 2)};

        input->hook = {origin.x - 10, origin.y + 75, 25, 25};
        input->hookCenter = {input->hook.x + (input->hook.width / 2),
                             input->hook.y + (input->hook.height / 2)};

        output->hook = {origin.x + RELAY_WIDTH, origin.y + 50, 25, 25};
        output->hookCenter = {output->hook.x + (output->hook.width / 2),
                              output->hook.y + (output->hook.height / 2)};
    }
};

#endif