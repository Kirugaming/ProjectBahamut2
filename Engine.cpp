//
// Created by kirut on 10/16/2023.
//

#include "Engine.h"


Engine::Engine() {
    SDL_GetCurrentDisplayMode(0, &displayMode);
    if (initRendering(
            (displayMode.h-50) / 1.1,
            (displayMode.w) / 1.1) != 0) {
        std::cout << "ENGINE_ERROR::INIT_RENDERING" << std::endl;
    }

    // init engine ui

    // init game
    game.camera = Camera(glm::vec3(0.0f, 1.5f, 2.0f));

    auto* model = new GameObject("Raphtalia", Model("raph/raph.obj"));
    model->transform.position = glm::vec3(0.0f, -0.5f, 0.0f);
    model->transform.rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0f));
    game.models.push_back(model);
}

/*
 * Startup SDL rendering and OpenGL rendering
 */
int Engine::initRendering(int winHeight, int winWidth) {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL FAILED TO INITIALIZE!\n " << SDL_GetError() << std::endl;
        return -1;
    }
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
    glViewport(0, 0, winWidth, winHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    return 0;
}

void Engine::engineLoop() {
    while(!game.quit){
        eventMonitor(); // query SDL events

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glClearColor(.2f, .3f, .3f, 1.0f);

        for (GameObject* model : game.models) {
            model->draw();
        }


        SDL_GL_SwapWindow(window);
    }
}


void Engine::eventMonitor() {
    while( SDL_PollEvent( &e ) ) {
        if( e.type == SDL_QUIT ) {
            game.quit = true;
        } else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) { // Resize OpenGL context
            glViewport(0, 0, e.window.data1, e.window.data2);
        }
    }
}

Engine::~Engine() {
    // cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow( window );
    SDL_Quit();
}