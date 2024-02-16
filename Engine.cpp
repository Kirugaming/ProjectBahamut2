//
// Created by kirut on 10/16/2023.
//

#include "Engine.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


Engine::Engine(Project &chosenProject) : project(chosenProject) {
    SDL_GetCurrentDisplayMode(0, &displayMode);
    if (initRendering(
            (int) windowSize.height,
            (int) windowSize.width)) {
        std::cerr << "ENGINE_ERROR::INIT_RENDERING" << std::endl;
    }

    baseShader = new Shader();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEBUG_OUTPUT);
}

/*
 * Startup SDL rendering and OpenGL rendering
 */
int Engine::initRendering(int winHeight, int winWidth) {
    // Create Window
    window = SDL_CreateWindow("ProjectBahamut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);

    // opengl
    SDL_GL_LoadLibrary(nullptr);
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
    glContext = SDL_GL_CreateContext(window);
    // Init Glad
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cerr << "Glad failed to Initialize!" << std::endl;
        return -1;
    }

    return 0;
}

void Engine::engineLoop() {
    while(!quit) {
        deltaTime.update();

        // Events
        SDL_PumpEvents();
        eventMonitor(); // query SDL events
        KeyboardInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(.2f, .3f, .3f, 1.0f);

        baseShader->use();

        for (Brush *brush: map.brushList) {
            drawMeshSubClass(brush);
        }
        drawGameObjects(map.gameObjects);

        baseShader->unUse();

        ui->renderUI();

        SDL_GL_SwapWindow(window);
    }
}


void Engine::eventMonitor() {
    while( SDL_PollEvent( &event ) ) {
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        windowSize.height = event.window.data1;
                        windowSize.width = event.window.data2;
                        break;
                }
                break;
        }
    }
}

Engine::~Engine() {
    // cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void Engine::KeyboardInput() { // possible to do this elsewhere but its here for now
    if (inputManager.getKeyDown("w")) {
        camera.movement(Camera::FORWARD, deltaTime.get());
    }
    if (inputManager.getKeyDown("s")) {
        camera.movement(Camera::BACKWARD, deltaTime.get());
    }
    if (inputManager.getKeyDown("a")) {
        camera.movement(Camera::LEFT, deltaTime.get());
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

void Engine::drawGameObjects(const std::vector<GameObject*>& gameObjects) const {
    for (GameObject* model : gameObjects) {
        for (Script *script : model->scripts) {
            script->run();
        }

        baseShader->editShaderWithMat4("view", camera.getView());
        baseShader->editShaderWithMat4("perspective", glm::perspective(glm::radians(45.0f), 1.88791f, 0.1f, 100.0f));
        model->draw(*baseShader);

        drawGameObjects(model->nestedGameObjects);
    }
}

void Engine::drawMeshSubClass(Mesh *mesh) {
    baseShader->editShaderWithMat4("view", camera.getView());
    baseShader->editShaderWithMat4("perspective", glm::perspective(glm::radians(45.0f), 1.88791f, 0.1f, 100.0f));
    mesh->draw(*baseShader);

}
