//
// Created by kirut on 7/24/2024.
//

#ifndef PROJECTBAHAMUT_BASESDLWINDOW_H
#define PROJECTBAHAMUT_BASESDLWINDOW_H


#include "BaseWindow.h"

static bool sdlStarted = false;

class BaseSDLWindow : protected BaseWindow {

protected:
    SDL_Window* sdlWindow;
    SDL_GLContext glContext;
    SDL_DisplayMode displayMode;
    SDL_Event event;

    BaseSDLWindow();
    ~BaseSDLWindow();
    void eventMonitor();

public:
};


#endif //PROJECTBAHAMUT_BASESDLWINDOW_H
