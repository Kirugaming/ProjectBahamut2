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
#include "InputManager.h"
#include "Brush.h"

struct DeltaTime {
    void update() {
        lastFrame = currentFrame;
        currentFrame = (float) SDL_GetPerformanceCounter();
    }
    [[nodiscard]] float get() const {
        return currentFrame - lastFrame;
    }
private:
    float lastFrame = 0.0f;
    float currentFrame = 0.0f;
};

class Engine {
public:
    Map map;
    Mesh test;

    Engine();
    ~Engine();

    void draw();
    void createRay(glm::vec3 normMousePos);
    void setAspectRatio(float inAspectRatio);
private:
    InputManager &inputManager = InputManager::getInstance();
    DeltaTime deltaTime;
    Shader *baseShader;
    float aspectRatio = 0;
    Camera camera = Camera(glm::vec3(0.0f, 0.0f, 2.0f));
    std::vector<BaseDrawable*> drawables;

    void drawBrush(Brush *brush);
    void drawGameObjects(const std::vector<GameObject*>& gameObjects) const;
    void checkInputs();
};


#endif //PROJECTBAHAMUT_ENGINE_H
