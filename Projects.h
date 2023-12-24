//
// Created by kirut on 10/21/2023.
//

#ifndef PROJECTBAHAMUT_PROJECTS_H
#define PROJECTBAHAMUT_PROJECTS_H

#include <string>

#include "sdl.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include <yaml-cpp/yaml.h>

static struct Project {
    std::string name;
    std::string path;
    // last edited

} project;

class ProjectsWindow {
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    bool quit = false;
    bool isMakeNewProjectOpen = false;
    Project *newProject = nullptr;
    std::vector<Project> projectList;

    void renderUi();
    void openProjectFile();
    void makeNewProject();
    void appendNewProject();


public:
    Project *selectedProject = nullptr;
    ProjectsWindow();
    ~ProjectsWindow();
    void renderLoop();

};


#endif //PROJECTBAHAMUT_PROJECTS_H
