//
// Created by kirut on 10/20/2023.
//

#include "engineUI.h"
#include "Script.h"


engineUI::engineUI(SDL_Window *window, SDL_GLContext &glContext){

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();

    // load icons
    icons["folderClosed"] = new Texture(R"(D:\Projects\C++\ProjectBahamut2\Assets\icons\folder-solid.png)");
    icons["folderOpen"] = new Texture(R"(D:\Projects\C++\ProjectBahamut2\Assets\icons\folder-open-regular.png)");
    icons["object"] = new Texture(R"(D:\Projects\C++\ProjectBahamut2\Assets\icons\cube-solid.png)");

}

engineUI::~engineUI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void engineUI::renderUI(Game *game) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    projectFileExplorer();

    ImGuiWindowFlags guiWindowFlags = 0;
    guiWindowFlags |= ImGuiWindowFlags_NoMove;
    guiWindowFlags |= ImGuiWindowFlags_NoResize;
    guiWindowFlags |= ImGuiWindowFlags_NoCollapse;
    guiWindowFlags |= ImGuiWindowFlags_NoNav;
    guiWindowFlags |= ImGuiWindowFlags_NoTitleBar;

    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 0), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(320, 300), ImGuiCond_Once);

    ImGui::Begin("Game Object Editor", reinterpret_cast<bool *>(true), guiWindowFlags);

    ImGui::Text("Game Object Editor");
    ImGui::SameLine();
    if (ImGui::Button("Save Map")) {
        engine->game.level->save();
    }

    ImGui::Separator();
    ImGui::Text("Game Objects:");

    for (auto object : game->level->gameObjects) {
        ImGui::Image((void*)(intptr_t)icons["object"]->id, ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::SameLine();
        if (object->name.empty()) {
            if (ImGui::Button("##")) {
                this->selectedObject = object;
            }
        } else if (ImGui::Button(object->name.c_str())) {
            this->selectedObject = object;
        }
    }

    if (selectedObject != nullptr) {
        objectEditWindow(selectedObject);
    }

    ImGui::End();

    //ImGui::ShowDemoWindow();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void engineUI::objectEditWindow(GameObject *gameObject) {
    ImGui::SetNextWindowSize(ImVec2(320, 300), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 300), ImGuiCond_Once);
    ImGui::Begin("Object Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("This is the object editor window!");
    ImGui::Separator();
    ImGui::Text("Object Name:");  // Where users can edit the name of game objects
    char buffer[256];
    strcpy(buffer, gameObject->name.c_str());
    if (ImGui::InputText("##Object Name", buffer, 256)) {
        gameObject->name = buffer;
    };

    ImGui::Separator();
    // where users can change various transformation stuff
    ImGui::Text("Object Position:");
    glm::vec3 position = gameObject->transform.position;
    if (ImGui::DragFloat3("##Position xyz", glm::value_ptr(position), 0.005f)) {
        gameObject->transform.position = position;
    }
    ImGui::Separator();
    ImGui::Text("Object Rotation:");
    glm::vec3 rotation = glm::eulerAngles(gameObject->transform.rotation);
    if (ImGui::DragFloat3("##Rotation xyz", glm::value_ptr(rotation), 0.005f)) {
        gameObject->transform.rotation = glm::quat(rotation);
    }
    ImGui::Separator();
    ImGui::Text("Object Scale:");
    glm::vec3 scale = gameObject->transform.scale;
    if (ImGui::DragFloat3("##Scale xyz", glm::value_ptr(scale), 0.005f)) {
        gameObject->transform.scale = scale;
    }
    ImGui::Separator();

    ImGui::End();
}

void engineUI::projectFileExplorer() {
    ImGui::SetNextWindowSize(ImVec2(320, ImGui::GetIO().DisplaySize.y), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("Project Explorer", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("Project Explorer");
    ImGui::Separator();

    displayFileTree(engine->project.path, 0);


    ImGui::End();
}
/*
 * Recursively goes through files from project root and make button for each
 * if directory then does function again
 */
void engineUI::displayFileTree(const std::string &path, int level) {
    std::string tabs(level, '\t');
    if (level > 0) {
        tabs += "-";
    }

    for (const auto &file : std::filesystem::directory_iterator(path)) {
        auto fileName = file.path().filename().string();
        ImGui::Text(tabs.c_str()); // it would be nice if UNICODE CHARACTERS WORKED
        ImGui::SameLine();

        if (file.is_directory()) {
            // find if directory is open in ui
            bool isOpen = openFolders.find(file.path().string()) != openFolders.end();

            ImGui::Image((void*)(intptr_t)(isOpen ? icons["folderOpen"]->id : icons["folderClosed"]->id), ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0));
            ImGui::SameLine();

            if (ImGui::Button(fileName.c_str())) {
                // path is added to open directories if not open
                if (!isOpen) {
                    openFolders.insert(file.path().string());
                } else {
                    openFolders.erase(file.path().string());
                }
            }

            if (isOpen) {
                displayFileTree(file.path().string(), level + 1);
            }
        } else {

            if (ImGui::Button(fileName.c_str())) { // do file action
                if (fileName.substr(fileName.length()-4, fileName.length()) == "yaml") {
                    selectedObject = nullptr;
                    engine->game.level = new Level(file.path().string());
                }
            }
        }
    }
}
