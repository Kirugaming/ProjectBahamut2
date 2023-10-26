//
// Created by kirut on 10/16/2023.
//

#include "Engine.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"


Engine::Engine(Project &chosenProject) : project(chosenProject) {
    SDL_GetCurrentDisplayMode(0, &displayMode);
    if (initRendering(
            (displayMode.h-50),
            (displayMode.w) != 0)) {
        std::cout << "ENGINE_ERROR::INIT_RENDERING" << std::endl;
    }



    // init game
    game.camera = Camera(glm::vec3(0.0f, 1.0f, 2.0f));

    game.level = new Level(project.path, project.path + "/test.yaml");

    // init engine ui
    ui = new engineUI(window, glContext, project);
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
    glViewport(0, 0, winWidth / 2, winHeight / 2);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

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

        for (GameObject* model : game.level->gameObjects) {
            model->draw(game.camera.getView());
        }

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
                        glViewport(event.window.data1 / 6, event.window.data2 / 3, event.window.data1 / 1.5, event.window.data2 / 1.5);
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
    if (keys[SDL_SCANCODE_W]) {
        game.camera.movement(Camera::FORWARD, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_S]) {
        game.camera.movement(Camera::BACKWARD, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_A]) {
        game.camera.movement(Camera::LEFT, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_D]) {
        game.camera.movement(Camera::RIGHT, game.deltaTime);
    }
    if (keys[SDL_SCANCODE_UP]) {
        game.camera.setPitch(1);
    }
    if (keys[SDL_SCANCODE_DOWN]) {
        game.camera.setPitch(-1);
    }
    if (keys[SDL_SCANCODE_LEFT]) {
        game.camera.setYaw(-1);
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        game.camera.setYaw(1);
    }
}
