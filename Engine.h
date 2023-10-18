//
// Created by kirut on 10/16/2023.
//

#ifndef PROJECTBAHAMUT_ENGINE_H
#define PROJECTBAHAMUT_ENGINE_H

// provides blueprint for keyboard input, game editor window, and engine UI


#include <vector>
#include <chrono>
#include "Camera.h"
#include "GameObject.h"
#include "SDL.h"
#include "imgui.h"

struct Game {
    bool quit;
    Camera camera;
    float deltaTime = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::chrono::time_point<std::chrono::steady_clock> lastFrame;
    std::vector<GameObject*> models;
};

class Engine {
public:
    SDL_DisplayMode displayMode;
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;
    SDL_Event *event;
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);

    bool rightMouseButtonPressed = false;
    int initialMouseX = 0;
    int initialMouseY = 0;

    Game game;
    // Dear Imgui to be implemented
    Engine();
    ~Engine();


    void engineLoop();



private:
    int initRendering(int winHeight, int winWidth); // SDL and OpenGL
    int initEngineUI();
    void eventMonitor();

    void KeyboardInput();
};


#endif //PROJECTBAHAMUT_ENGINE_H
