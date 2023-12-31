//
// Created by kirut on 10/22/2023.
//

#ifndef PROJECTBAHAMUT_GAME_H
#define PROJECTBAHAMUT_GAME_H


#include <chrono>
#include "Camera.h"
#include "Level.h"

class Game {

public:
    bool quit{};
    Camera camera;
    Level *level = nullptr;
    float deltaTime;
    float lastFrame;

    Game();

    void computeDeltaTime();
};


#endif //PROJECTBAHAMUT_GAME_H
