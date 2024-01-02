//
// Created by kirut on 10/20/2023.
//

#include "engineUI.h"
#include "Script.h"


engineUI::engineUI(SDL_Window *window, SDL_GLContext &glContext) {

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();

    // setup top down brush viewer





    loadUiIcons();
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

    configureNextWindowPosSize(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 0),
                               ImVec2(320, 300));

    ImGui::Begin("Game Object Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("Game Object Editor");
    ImGui::SameLine();
    if (ImGui::Button("Save Map")) {
        engine->game.level->save();
    }

    ImGui::Separator();

    if (ImGui::TreeNode("Map Geometry")) {
        for (Brush *brush : game->level->brushList) {
            if (brush->name.empty()) {
                if (ImGui::Button("##")) {
                    selectedObject = nullptr;
                    this->selectedBrush = brush;
                }
            } else {
                if (ImGui::Button(brush->name.c_str())) {
                    selectedObject = nullptr;
                    selectedBrush = brush;
                }
            }
        }
        ImGui::TreePop();
    }
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("Add Cube Brush")) {
            game->level->brushList.push_back(new Brush());
        }
        ImGui::EndPopup();
    }
    if (ImGui::TreeNode("Game Objects")) {
        drawGameObjectButton(game->level->gameObjects);
        ImGui::TreePop();
    }




    if (selectedObject != nullptr) {

        objectEditWindow(selectedObject);
    }
    if (selectedBrush != nullptr) {

        brushEditWindow(selectedBrush);
    }

    ImGui::End();

    ImGui::ShowDemoWindow();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void engineUI::objectEditWindow(GameObject *gameObject) {
    configureNextWindowPosSize(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 300),
                               ImVec2(320, 300));
    ImGui::Begin("Object Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("This is the object editor window!");

    gameObject->name = drawTextInput("Object Name", gameObject->name);

    drawVec3Input("Object Position", gameObject->transform.position);
    drawVec3Input("Object Rotation", gameObject->transform.rotation);
    drawVec3Input("Object Scale", gameObject->transform.scale);

    ImGui::Separator();
    ImGui::Text("Attached Scripts:");
    for (int i = 0; i < gameObject->scripts.size(); ++i) {
        ImGui::Text(gameObject->scripts[i]->path.filename().string().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete")) {
            gameObject->scripts.erase(gameObject->scripts.begin() + i);
        }
    }



    ImGui::Button("Drop New Script Here", ImVec2(320, 50));
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_SCRIPT_FILE")) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);
            ImGui::BeginTooltip();
            ImGui::Text("Drop Script here to add to game object");
            ImGui::EndTooltip();
            gameObject->scripts.push_back(new Script(static_cast<char*>(payload->Data), gameObject)); // turn the void pointer to string :)
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}

void engineUI::projectFileExplorer() {
    configureNextWindowPosSize(ImVec2(0, 0),
                               ImVec2(320, ImGui::GetIO().DisplaySize.y));
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

    for (const auto &file: std::filesystem::directory_iterator(path)) {
        auto fileName = file.path().filename().string();
        ImGui::Text(tabs.c_str()); // it would be nice if UNICODE CHARACTERS WORKED
        ImGui::SameLine();

        if (file.is_directory()) {
            // find if directory is open in ui
            bool isOpen = openFolders.find(file.path().string()) != openFolders.end();

            ImGui::Image((void *) (intptr_t) (isOpen ? icons["folderOpen"]->id : icons["folderClosed"]->id),
                         ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0));
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
            handleFileTypes(file);
        }
    }
}

void engineUI::handleFileTypes(const std::filesystem::directory_entry& file) {
    auto fileName = file.path().filename().string();
    std::string fileType = fileName.substr(fileName.find('.') + 1, fileName.length());

    if (fileType == "lua") { // some files have drag drop and some don't
        if (ImGui::Button(fileName.c_str())) { // do file action
        }
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
            ImGui::SetDragDropPayload("DRAG_SCRIPT_FILE", file.path().string().c_str(),
                                      file.path().string().capacity()); // i don't know why capacity works and not size
            ImGui::Text(fileName.c_str());
            ImGui::EndDragDropSource();
        }
    } else { // normal button
        if (ImGui::Button(fileName.c_str())) { // do file action
            if (fileType == "bem") {
                selectedObject = nullptr;
                engine->game.level = new Level(file.path().string());
            }
        }
    }
}

void engineUI::loadUiIcons() {
    icons["folderClosed"] = new Texture(R"(Assets\icons\folder-solid.png)");
    icons["folderOpen"] = new Texture(R"(Assets\icons\folder-open-regular.png)");
    icons["object"] = new Texture(R"(Assets\icons\cube-solid.png)");
}

void engineUI::configureNextWindowPosSize(ImVec2 position, ImVec2 size) {
    ImGui::SetNextWindowPos(position, ImGuiCond_Once);
    ImGui::SetNextWindowSize(size, ImGuiCond_Once);
}

void engineUI::drawVec3Input(const std::string &inputName, glm::vec3 &vector3) {
    ImGui::Separator();
    ImGui::Text((inputName + ":").c_str());
    glm::vec3 vec3Buffer = vector3;
    if (ImGui::DragFloat3(("##" + inputName).c_str(), glm::value_ptr(vector3), 0.005f)) {

    }
}

std::string engineUI::drawTextInput(const std::string &inputName, std::string &text) {
    ImGui::Separator();
    ImGui::Text((inputName + ":").c_str());

    char buffer[256];
    strcpy(buffer, text.c_str());

    if (ImGui::InputText(("##" + inputName).c_str(), buffer, 256)) {
        text = buffer;
    }

    return text;
}

void engineUI::drawGameObjectButton(std::vector<GameObject*> &gameObjects) {
    for (auto& object : gameObjects) {
        ImGui::Image((void*)(intptr_t)icons["object"]->id, ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::SameLine();
        if (object->name.empty()) {
            if (ImGui::Button("##")) {
                selectedBrush = nullptr;
                this->selectedObject = object;
            }
        } else if (ImGui::TreeNode(object->name.c_str())) {
            this->selectedObject = object;
            selectedBrush = nullptr;
            drawGameObjectButton(selectedObject->nestedGameObjects);
            ImGui::TreePop();
        }
    }
}

void engineUI::brushEditWindow(Brush *brush) {
    configureNextWindowPosSize(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 300),
                               ImVec2(320, 300));

    ImGui::Begin("Object Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("This is the object editor window!");

    brush->name = drawTextInput("Object Name", brush->name);

    drawVec3Input("Object Position", brush->transform.position);
    drawVec3Input("Object Rotation", brush->transform.rotation);
    drawVec3Input("Object Scale", brush->transform.scale);

    ImGui::End();
}
