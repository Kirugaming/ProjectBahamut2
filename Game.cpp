//
// Created by kirut on 10/22/2023.
//

#include "Game.h"
#include "SDL.h"

Game::Game() {
    deltaTime = 0.0f;
    lastFrame = 0.0f;

}

void Game::computeDeltaTime() {
    auto now = (float) SDL_GetPerformanceCounter();
    deltaTime = (now - lastFrame) * 10 / (float) SDL_GetPerformanceFrequency();
    lastFrame = now;
}