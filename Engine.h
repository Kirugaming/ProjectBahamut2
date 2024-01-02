//
// Created by kirut on 10/16/2023.
//

#ifndef PROJECTBAHAMUT_ENGINE_H
#define PROJECTBAHAMUT_ENGINE_H



#include <vector>
#include <chrono>
#include "Camera.h"
#include "GameObject.h"
#include "SDL.h"
#include "imgui.h"
#include "Level.h"
#include "engineUI.h"
#include "Game.h"
#include "Projects.h"
#include "InputManager.h"
#include "Brush.h"

class engineUI;

static struct WindowSize {
    int height;
    int width;
} windowSize;

class Engine {
public:
    SDL_DisplayMode displayMode;
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;
    SDL_Event event;


    WindowSize windowSize;
    Project project;
    Game game;
    bool isWireframeModeEnabled = false;

    InputManager &inputManager = InputManager::getInstance();
    engineUI *ui;


    // Dear Imgui to be implemented
    Engine(Project &chosenProject);
    ~Engine();


    void engineLoop();



private:
    Shader *baseShader; // make this so its made after opengl context is created

    int initRendering(int winHeight, int winWidth); // SDL and OpenGL
    void eventMonitor();
    void KeyboardInput();
    void drawMeshSubClass(Mesh *mesh);
    void drawGameObjects(const std::vector<GameObject*>& gameObjects) const;
};


#endif //PROJECTBAHAMUT_ENGINE_H
