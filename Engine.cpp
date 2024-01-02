//
// Created by kirut on 10/16/2023.
//

#include "Engine.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


Engine::Engine(Project &chosenProject) : project(chosenProject), windowSize(displayMode.h-50, (displayMode.w) != 0) {
    SDL_GetCurrentDisplayMode(0, &displayMode);
    if (initRendering(
            (int) windowSize.height,
            (int) windowSize.width)) {
        std::cout << "ENGINE_ERROR::INIT_RENDERING" << std::endl;
    }

    baseShader = new Shader();



    // init game
    game.camera = Camera(glm::vec3(0.0f, 0.0f, 2.0f));

    game.level = new Level();

    // init engine ui

    glViewport(windowSize.height / 6, windowSize.width / 6, windowSize.height / 1.5, windowSize.width / 1.5);
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
        std::cout << "Glad failed to Initialize!" << std::endl;
        return -1;
    }

    // OpenGL rendering settings
//    viewportPosHW += glm::vec4(winWidth/ 6, winHeight / 3, winWidth / 1.5, winHeight / 1.5);
//    std::cout << viewportPosHW.x << " " << viewportPosHW.y << " " << viewportPosHW.z << " " << viewportPosHW.w << " " << std::endl;


    return 0;
}

void Engine::engineLoop() {
    while(!game.quit){
        game.computeDeltaTime();

        // Events
        SDL_PumpEvents();
        eventMonitor(); // query SDL events
        KeyboardInput();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(.2f, .3f, .3f, 1.0f);



        baseShader->use();

        if (isWireframeModeEnabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        for (Brush *brush: game.level->brushList) {
            drawMeshSubClass(brush);
        }

        if (isWireframeModeEnabled) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        drawGameObjects(game.level->gameObjects);
        baseShader->unUse();



        ui->renderUI(&game);

        SDL_GL_SwapWindow(window);
    }
}


void Engine::eventMonitor() {
    while( SDL_PollEvent( &event ) ) {
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend
        switch (event.type) {
            case SDL_QUIT:
                game.quit = true;
                break;
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                    case SDL_WINDOWEVENT_RESIZED:
                        windowSize.height = event.window.data1;
                        windowSize.width = event.window.data2;
//                        viewportPosHW = glm::vec4(event.window.data1/ 6, event.window.data2 / 3, event.window.data1 / 1.5, event.window.data2 / 1.5);
//                        glViewport(viewportPosHW.x, viewportPosHW.y, viewportPosHW.z, viewportPosHW.w);
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
        game.camera.movement(Camera::FORWARD, game.deltaTime);
    }
    if (inputManager.getKeyDown("s")) {
        game.camera.movement(Camera::BACKWARD, game.deltaTime);
    }
    if (inputManager.getKeyDown("a")) {
        game.camera.movement(Camera::LEFT, game.deltaTime);
    }
    if (inputManager.getKeyDown("d")) {
        game.camera.movement(Camera::RIGHT, game.deltaTime);
    }
    if (inputManager.getKeyDown("up")) {
        game.camera.setPitch(1);
    }
    if (inputManager.getKeyDown("down")) {
        game.camera.setPitch(-1);
    }
    if (inputManager.getKeyDown("left")) {
        game.camera.setYaw(-1);
    }
    if (inputManager.getKeyDown("right")) {
        game.camera.setYaw(1);
    }
    if (inputManager.getKeyDown("tab")) {
        if (isWireframeModeEnabled) {
            isWireframeModeEnabled = false;
        } else {
            isWireframeModeEnabled = true;
        }
    }
}

void Engine::drawGameObjects(const std::vector<GameObject*>& gameObjects) const {
    for (GameObject* model : gameObjects) {
        for (Script *script : model->scripts) {
            script->run();
        }

        baseShader->editShaderWithMat4("view", game.camera.getView());
        baseShader->editShaderWithMat4("perspective", glm::perspective(glm::radians(45.0f), 1.88791f, 0.1f, 100.0f));
        model->draw(*baseShader);

        drawGameObjects(model->nestedGameObjects);
    }
}

void Engine::drawMeshSubClass(Mesh *mesh) {
    baseShader->editShaderWithMat4("view", game.camera.getView());
    baseShader->editShaderWithMat4("perspective", glm::perspective(glm::radians(45.0f), 1.88791f, 0.1f, 100.0f));
    mesh->draw(*baseShader);

}
