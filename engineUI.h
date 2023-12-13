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
class Engine;



class engineUI {
public:
    Engine *engine;

    engineUI(SDL_Window *window, SDL_GLContext &glContext);
    ~engineUI();

    void renderUI(Game *game);

private:
    std::map<std::string, Texture*> icons;
    GameObject *selectedObject = nullptr;
    std::unordered_set<std::string> openFolders;
    std::string *fileDragTemp;

    void objectEditWindow(GameObject *gameObject);
    void loadUiIcons();
    static void configureNextWindowPosSize(ImVec2 position, ImVec2 size);
    static glm::vec3 drawVec3Input(const std::string& inputName, glm::vec3 &vector3);
    static std::string drawTextInput(const std::string& inputName, std::string &text);
    void drawGameObjectButton(std::vector<GameObject*> &gameObjects);
    void projectFileExplorer();
    void displayFileTree(const std::string &path, int level);
    void handleFileTypes(const std::filesystem::directory_entry& file);

    void openFile(std::string path);
};


#endif //PROJECTBAHAMUT_ENGINEUI_H
