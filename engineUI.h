//
// Created by kirut on 10/20/2023.
//

#ifndef PROJECTBAHAMUT_ENGINEUI_H
#define PROJECTBAHAMUT_ENGINEUI_H

struct Game;

#include "SDL_video.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "Engine.h"




class engineUI {
public:
    engineUI(SDL_Window *window, SDL_GLContext &glContext);

    ~engineUI();

    void renderUI(Game *game);

private:
    GameObject *selectedObject = nullptr;
    void objectEditWindow(GameObject *gameObject);
};


#endif //PROJECTBAHAMUT_ENGINEUI_H
