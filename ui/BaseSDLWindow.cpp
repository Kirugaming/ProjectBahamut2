//
// Created by kirut on 7/24/2024.
//

#include "BaseSDLWindow.h"
#include "backends/imgui_impl_sdl2.h"

BaseSDLWindow::BaseSDLWindow() {
    if (!sdlStarted) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cerr << "SDL FAILED TO INITIALIZE!\n " << SDL_GetError() << std::endl;
            throw std::exception();
        }
        SDL_GL_LoadLibrary(nullptr);
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 6 );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

        sdlStarted = true;
    }
}

void BaseSDLWindow::eventMonitor() {
    while( SDL_PollEvent( &event ) ) {
        ImGui_ImplSDL2_ProcessEvent(&event); // Forward your event to backend
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
        }
    }
}

BaseSDLWindow::~BaseSDLWindow() {
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}
