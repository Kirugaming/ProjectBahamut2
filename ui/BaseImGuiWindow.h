//
// Created by kirut on 7/22/2024.
//

#ifndef PROJECTBAHAMUT_BASEIMGUIWINDOW_H
#define PROJECTBAHAMUT_BASEIMGUIWINDOW_H


#include <map>
#include "BaseWindow.h"
#include "BaseImGuiWindow.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

static const std::map<std::string, Texture> *ICONS = nullptr;
static bool imguiStarted = false;


class ProjectsWindow;

class BaseImGuiWindow : protected BaseWindow {

protected:
    static Engine* engine;
    ImGuiWindowFlags winFlags;
    static ImGuiViewport* viewport;

    BaseImGuiWindow();
    bool hasBeenResized();
public:
    void draw() override{};
    static void startImGui(SDL_Window* sdlWindow, SDL_GLContext glContext);
    static void shutdownImGui();
};


#endif //PROJECTBAHAMUT_BASEIMGUIWINDOW_H
