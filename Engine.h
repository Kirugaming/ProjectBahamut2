//
// Created by kirut on 10/16/2023.
//

#ifndef PROJECTBAHAMUT_ENGINE_H
#define PROJECTBAHAMUT_ENGINE_H

// provides blueprint for keyboard input, game editor window, and engine UI


#include <vector>
#include "Camera.h"
#include "GameObject.h"
#include "SDL.h"

struct Game {
    bool quit;
    Camera camera;
    float deltaTime;
    std::vector<GameObject*> models;
};

class Engine {
public:
    SDL_DisplayMode displayMode;
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;
    SDL_Event e;

    Game game;
    // Dear Imgui to be implemented
    Engine();
    ~Engine();

    void eventMonitor();
    void engineLoop();




private:
    int initRendering(int winHeight, int winWidth); // SDL and OpenGL
};


#endif //PROJECTBAHAMUT_ENGINE_H
