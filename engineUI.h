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
#include <filesystem>
#include <unordered_set>

class Project;



class engineUI {
public:
    engineUI(SDL_Window *window, SDL_GLContext &glContext, Project &inProject);

    ~engineUI();

    void renderUI(Game *game);

private:
    Project &project;
    std::map<std::string, Texture*> icons;
    GameObject *selectedObject = nullptr;
    std::unordered_set<std::string> openFolders;

    void objectEditWindow(GameObject *gameObject);
    void projectFileExplorer();
    void displayFileTree(const std::string path, int level);
};


#endif //PROJECTBAHAMUT_ENGINEUI_H
