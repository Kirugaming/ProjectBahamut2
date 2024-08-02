//
// Created by kirut on 7/21/2024.
//

#include "MainWindow.h"
#include "imgui_internal.h"
#include "RenderWindow.h"
#include "backends/imgui_impl_sdl2.h"

MainWindow::MainWindow() : BaseSDLWindow() {
    SDL_GetCurrentDisplayMode(0, &displayMode);
    // Create Window
    sdlWindow = SDL_CreateWindow("ProjectBahamut", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, displayMode.w, displayMode.h,
                                 SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_MAXIMIZED);

    glContext = SDL_GL_CreateContext(sdlWindow);
    SDL_GL_MakeCurrent(sdlWindow, glContext);
    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        std::cerr << "Glad failed to Initialize!" << std::endl;
        throw std::exception();
    }

    BaseImGuiWindow::startImGui(sdlWindow, glContext);
    imGuiWindow = new DockspaceWindow();

    MainWindow::draw();
}
void MainWindow::draw() {
    while (!quit) {
        // Events
        SDL_PumpEvents();
        eventMonitor(); // query SDL events
        KeyboardInput();

        imGuiWindow->draw();

        SDL_GL_SwapWindow(sdlWindow);
    }
}

MainWindow::~MainWindow() {

}

void MainWindow::KeyboardInput() {

}

