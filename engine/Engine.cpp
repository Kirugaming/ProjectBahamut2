//
// Created by kirut on 10/16/2023.
//

#include "Engine.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"
#include "Line.h"


Engine::Engine() {
    baseShader = new Shader();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEBUG_OUTPUT);

    drawables.push_back(createGrid());
}

Engine::~Engine() = default;

void Engine::draw() {
    deltaTime.update();
    checkInputs();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(.2f, .3f, .3f, 1.0f);

    baseShader->use();

    baseShader->setMat4("view", camera.getView());
    baseShader->setMat4("perspective", glm::perspective(camera.fov, aspectRatio, 0.1f, 100.0f));

    for (BaseDrawable *drawable : drawables) {
        drawable->draw(*baseShader);
    }


    baseShader->setVec3("colors", glm::vec3(1.0f));
    test.draw(*baseShader);

    baseShader->unUse();
}

void Engine::drawGameObjects(const std::vector<GameObject*>& gameObjects) const {
    for (GameObject* model : gameObjects) {
        for (Script *script : model->scripts) {
            script->run();
        }

        baseShader->setMat4("view", camera.getView());
        baseShader->setMat4("perspective", glm::perspective(camera.fov, aspectRatio, 0.1f, 100.0f));
        model->draw(*baseShader);

        drawGameObjects(model->nestedGameObjects);
    }
}

void Engine::drawBrush(Brush *brush) {
    baseShader->setMat4("view", camera.getView());
    baseShader->setMat4("perspective", glm::perspective(camera.fov, aspectRatio, 0.1f, 100.0f));
    brush->draw(*baseShader);
}

void Engine::setAspectRatio(float inAspectRatio) {
    this->aspectRatio = inAspectRatio;
}

void Engine::checkInputs() {
    if (inputManager.getKeyDown("w")) {
        camera.movement(Camera::FORWARD, deltaTime.get());
    }
    if (inputManager.getKeyDown("a")) {
        camera.movement(Camera::LEFT, deltaTime.get());
    }
    if (inputManager.getKeyDown("s")) {
        camera.movement(Camera::BACKWARD, deltaTime.get());
    }
    if (inputManager.getKeyDown("d")) {
        camera.movement(Camera::RIGHT, deltaTime.get());
    }
    if (inputManager.getKeyDown("up")) {
        camera.setPitch(1);
    }
    if (inputManager.getKeyDown("down")) {
        camera.setPitch(-1);
    }
    if (inputManager.getKeyDown("left")) {
        camera.setYaw(-1);
    }
    if (inputManager.getKeyDown("right")) {
        camera.setYaw(1);
    }
}

void Engine::createRay(glm::vec3 normMousePos) {
    // 4d homogeneous clip coords
    glm::vec4 rayClip(normMousePos.x, normMousePos.y, -1.0f, 1.0f);
    // 4d camera coordinates
    glm::vec4 rayEye = glm::inverse(glm::perspective(camera.fov, aspectRatio, 0.1f, 100.0f)) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0f, 0.0f);
    // 4d world coordinates
    glm::vec3 rayWorld = glm::normalize(glm::inverse(camera.getView()) * rayEye);

    if (test.isAABBIntersect(camera.position, rayWorld)) {

    }
}

Line* Engine::createGrid() {
    std::vector<glm::vec3> vertices;
    const int gridSize = 100;

    for (int i = -gridSize; i < gridSize; ++i) {
        // vertical
        vertices.emplace_back(i, 0.0f, -gridSize);
        vertices.emplace_back(i, 0.0f, gridSize);
        // horizontal
        vertices.emplace_back(-gridSize, 0.0f, i);
        vertices.emplace_back(gridSize, 0.0f, i);
    }

    return new Line(vertices, glm::vec3(0.75f));
}

