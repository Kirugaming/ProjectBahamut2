//
// Created by kirut on 10/20/2023.
//

#ifndef PROJECTBAHAMUT_ENGINEUI_H
#define PROJECTBAHAMUT_ENGINEUI_H


#include "SDL_video.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "Engine.h"
#include "Types.h"
#include <filesystem>
#include <unordered_set>
#include <map>

class Project;
class Engine;

static const std::map<std::string, Texture> *ICONS = nullptr;

class engineUI {

    struct RenderWindow {
        void draw();
        void initTexture();
    private:
        unsigned int FBO{};
        unsigned int renderTextureId{};
        int winWidth = 1280;
        int winHeight = 740;

        void handleResizing();
    };

    struct EditWindow {
        void draw();
        void setSelected(GameObject *gameObject);
        void setSelected(Brush *brush);
        void clearSelected();
    private:
        GameObject *selectedObject = nullptr;
        Brush *selectedBrush = nullptr;

        void objectEditDraw();
        void brushEditDraw();
        static void drawVec3Input(const std::string& inputName, glm::vec3 &vector3);
        static std::string drawTextInput(const std::string& inputName, std::string &text);
        void drawGameObjectButton(std::vector<GameObject*> &gameObjects);
    };

    struct FileExplorerWindow {
        void draw();
    private:
        static std::unordered_set<std::string> openFolders;
        std::string *fileDragTemp;

        void displayFileTree(const std::string &path, int level);
        void handleFileTypes(const std::filesystem::directory_entry& file);
    };

    static RenderWindow renderWindow;
    static EditWindow editWindow;
    static FileExplorerWindow fileExplorerWindow;

    static void configureNextWindowPosSize(vec2 position, vec2 size);
    static void initIcons();

public:
    static Engine *engine;

    engineUI(SDL_Window *window, SDL_GLContext &glContext);
    ~engineUI();

    static void renderUI();
};

#endif //PROJECTBAHAMUT_ENGINEUI_H
