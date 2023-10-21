//
// Created by kirut on 10/20/2023.
//

#include "engineUI.h"


engineUI::engineUI(SDL_Window *window, SDL_GLContext &glContext) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();
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
    ImGui::Separator();
    ImGui::Text("Game Objects:");

    for (auto object : game->level->gameObjects) {
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
