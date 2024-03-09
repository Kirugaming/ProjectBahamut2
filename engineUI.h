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
        explicit RenderWindow(engineUI &parent) : ui(parent) {};

        void draw();
        void initTexture();
        [[nodiscard]] float getAspectRatio() const;
    private:
        engineUI &ui;
        unsigned int FBO{};
        unsigned int renderTextureId{};
        int winWidth = 1280;
        int winHeight = 740;
        vec2 mousePos = {0, 0};

        void handleResizing();
        void mouseRelativeToRender();
    };

    struct EditWindow {
        explicit EditWindow(engineUI &parent) : ui(parent) {};

        void draw();
        void setSelected(GameObject *gameObject);
        void setSelected(Brush *brush);
        void clearSelected();
    private:
        engineUI &ui;
        GameObject *selectedObject = nullptr;
        Brush *selectedBrush = nullptr;

        void objectEditDraw();
        void brushEditDraw();
        static void drawVec3Input(const std::string& inputName, glm::vec3 &vector3);
        static std::string drawTextInput(const std::string& inputName, std::string &text);
        void drawGameObjectButton(std::vector<GameObject*> &gameObjects);
    };

    struct FileExplorerWindow {
        explicit FileExplorerWindow(engineUI &parent) : ui(parent) {};

        void draw();
    private:
        engineUI &ui;
        static std::unordered_set<std::string> openFolders;
        std::string *fileDragTemp = nullptr;

        void displayFileTree(const std::string &path, int level);
        void handleFileTypes(const std::filesystem::directory_entry& file);
    };
    ImGuiIO io;

    void configureNextWindowPosSize(vec2 position, vec2 size);
    void initIcons();

public:
    Engine *engine;
    RenderWindow renderWindow = RenderWindow(*this);
    EditWindow editWindow = EditWindow(*this);
    FileExplorerWindow fileExplorerWindow = FileExplorerWindow(*this);

    engineUI(SDL_Window *window, SDL_GLContext &glContext);
    ~engineUI();

    void renderUI();
};

#endif //PROJECTBAHAMUT_ENGINEUI_H
