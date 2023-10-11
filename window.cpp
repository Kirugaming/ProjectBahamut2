//
// Created by kirut on 9/3/2023.
//

#include "window.h"
#include "GameObject.h"


// SDL Rendering is for Engine UI,
// OpenGL is for game rendering and game ui and what not

int main(int argc, char *argv[]) {
    if (initWindow() == -1) {
        return -1;
    }

    glViewport(0, 0, winWidth, winHeight);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    auto* model = new GameObject("Raphtalia", Model("raph/raph.obj"));

    model->transform.position = glm::vec3(0.0f, -0.5f, 0.0f);
    model->transform.rotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 1.0, 0.0f));


    while(!quit){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        windowEvents();

        glClearColor(.2f, .3f, .3f, 1.0f);

        model->draw();


        SDL_GL_SwapWindow(window);
    }

    // cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}

/*
 * Startup SDL rendering and OpenGL rendering
 */
int initWindow() {
    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL FAILED TO INITIALIZE!\n " << SDL_GetError() << std::endl;
        return -1;
    }
    // Create Window and SDL OPENGL contexts
    SDL_GetCurrentDisplayMode(0, &displayMode);
    winWidth = (displayMode.w)/1.1;
    winHeight = (displayMode.h-50)/1.1;

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

    return 0;
}

void windowEvents() {
    while( SDL_PollEvent( &e ) ) {
        if( e.type == SDL_QUIT ) {
            quit = true;
        } else if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) { // Resize OpenGL context
            glViewport(0, 0, e.window.data1, e.window.data2);
        }
    }
}