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
#include "Map.h"
#include "engineUI.h"
#include "Projects.h"
#include "InputManager.h"
#include "Brush.h"

class engineUI;

static struct WindowSize {
    int height;
    int width;
} windowSize;

struct DeltaTime {
    void update() {
        currentFrame = (float) SDL_GetPerformanceCounter();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    [[nodiscard]] float get() const {
        return deltaTime;
    }

private:
    float lastFrame = 0.0f;
    float currentFrame = 0.0f;
    float deltaTime = 0.0f;
};

class Engine {
public:
    SDL_Window *window = nullptr;
    SDL_GLContext glContext = nullptr;
    WindowSize windowSize;
    Project project;
    Map map;

    Engine(Project &chosenProject);
    ~Engine();

    [[noreturn]] void engineLoop();
    void draw();

    engineUI *ui;
private:
    SDL_DisplayMode displayMode;
    SDL_Event event;
    InputManager &inputManager = InputManager::getInstance();
    bool quit = false;
    DeltaTime deltaTime;
    Shader *baseShader;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 2.0f));




    int initRendering(int winHeight, int winWidth); // SDL and OpenGL
    void eventMonitor();
    void KeyboardInput();
    void drawMeshSubClass(Mesh *mesh);
    void drawGameObjects(const std::vector<GameObject*>& gameObjects) const;
};


#endif //PROJECTBAHAMUT_ENGINE_H
