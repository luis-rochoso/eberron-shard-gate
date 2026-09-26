#include <bits/stdc++.h>
#include <string>
#include "states.hpp"
#include "interface.hpp"

struct InputConnector {
    Rectangle hook;
    Vector2 hookCenter;
    
    bool isPowered {false};
    bool isConnected {false};

    struct OutputConnector {
    Rectangle hook;
    Vector2 hookCenter;

    bool isPowered {false};

    std::vector<InputConnector*> linkeds;
    };

    OutputConnector* linked; // member of InputConnector
};



std::unordered_map<std::string, InputConnector> inputs;
std::unordered_map<std::string, InputConnector::OutputConnector> outputs;

InputConnector* dragged = nullptr;

struct Link {
    Vector2 start;
    Vector2 end;
};

std::list<Link> powerLines;

Vector2 mousePoint { 0.0f, 0.0f };
Vector2 dragLineStartPoint = { 0.0f, 0.0f };
Vector2 dragLineEndPoint { 0.0f, 0.0f };

bool shardPower[2] = {false, false};
bool exitPower = false;

std::unordered_map<std::string, Texture2D> textures;


// Handling pressing crystal buttons
void checkButtonPress() {
    for (int i = 0; i < 2; ++i) {
        if (CheckCollisionPointCircle(mousePoint, shardButtons[i].center, buttonRadius)) {
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                shardPower[i] = !shardPower[i];
            }
        }    
    }
}

// Lighting up or out the toggable shards  
void toggleLights() {
    for (int i = 0; i < 2; ++i) {
        shardLight[i] = shardPower[i];
    }
    exitLight = exitPower;
}

void eraseLink(InputConnector* dragged) {
    // procurar pelo start equivalente ao hookCenter na lista de links
    for (auto it = powerLines.begin(); it != powerLines.end(); ++it) {
        if (it->start.x == dragged->hookCenter.x and it->start.y == dragged->hookCenter.y) {
            powerLines.erase(it);
            return;
        }
    }
}

void buildConnectors() {

    // Shard connectors
    outputs["shard0"].hook = {PLATE_X + 80, shardButtons[0].center.y - 12.5f, 25, 25};
    outputs["shard1"].hook = {PLATE_X + 80, shardButtons[1].center.y - 12.5f, 25, 25};
    outputs["shard2"].hook = {PLATE_X + 80, shardButtons[1].center.y + 120 - 12.5f, 25, 25};

    outputs["shard0"].hookCenter = {outputs["shard0"].hook.x + (outputs["shard0"].hook.width / 2),
                                    outputs["shard0"].hook.y + (outputs["shard0"].hook.height / 2)};
    outputs["shard1"].hookCenter = {outputs["shard1"].hook.x + (outputs["shard1"].hook.width / 2),
                                    outputs["shard1"].hook.y + (outputs["shard1"].hook.height / 2)};
    outputs["shard2"].hookCenter = {outputs["shard2"].hook.x + (outputs["shard2"].hook.width / 2),
                                    outputs["shard2"].hook.y + (outputs["shard2"].hook.height / 2)};

    // Exit connector
    inputs["exit"].hook = {PLATE_X + PLATE_WIDTH - 20, shardButtons[1].center.y - 12.5f, 25, 25};
    inputs["exit"].hookCenter = {inputs["exit"].hook.x + (inputs["exit"].hook.width / 2),
                                 inputs["exit"].hook.y + (inputs["exit"].hook.height / 2)};
}

void powerConnectors() {

    outputs["shard0"].isPowered = shardPower[0];
    outputs["shard1"].isPowered = shardPower[1];
    outputs["shard2"].isPowered = true;


    if (inputs["exit"].isConnected) {
        inputs["exit"].isPowered = inputs["exit"].linked->isPowered;
    }
    else {
        inputs["exit"].isPowered = false;
    }
    exitPower = inputs["exit"].isPowered;

}

bool clickedInputConnector() {
    // Checks if the player clicked on an input hook
    for (auto& [label, connector] : inputs) {
        if (CheckCollisionPointRec(mousePoint, connector.hook) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            dragged = &connector;
            dragged->isConnected = false;
            eraseLink(dragged);
            return true;
        }
    }
    return false;
}

bool releasedOverOutputConnector() {
    // Checks if the link was released over an output hook
    for (auto& [label, connector] : outputs) {
        if (CheckCollisionPointRec(mousePoint, connector.hook) and IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            dragged->linked = &connector; // Input's connected only to this output
            dragged->isConnected = true;
            connector.linkeds.push_back(dragged); // Output adds this input to its list of connections
            return true;
        }
    }
    return false;
}



void getPower(InputConnector &connector) {
    if (connector.isConnected) {

    }
}