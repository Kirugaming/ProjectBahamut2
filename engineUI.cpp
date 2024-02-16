//
// Created by kirut on 10/20/2023.
//

#include "engineUI.h"
#include "Script.h"

Engine* engineUI::engine = nullptr;
engineUI::EditWindow engineUI::editWindow;
engineUI::FileExplorerWindow engineUI::fileExplorerWindow;
std::unordered_set<std::string> engineUI::FileExplorerWindow::openFolders;

engineUI::engineUI(SDL_Window *window, SDL_GLContext &glContext) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init();

    initIcons();
}

engineUI::~engineUI() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void engineUI::renderUI() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    fileExplorerWindow.draw();
    editWindow.draw();


    ImGui::ShowDemoWindow();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void engineUI::FileExplorerWindow::draw() {
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
void engineUI::FileExplorerWindow::displayFileTree(const std::string &path, int level) {
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

            ImGui::Image((void *) (intptr_t) (isOpen ? ICONS->find("folderOpen")->second.id : ICONS->find("folderClosed")->second.id),
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

void engineUI::FileExplorerWindow::handleFileTypes(const std::filesystem::directory_entry& file) {
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
                engineUI::editWindow.clearSelected();
                engine->map = *new Map(file.path().string());
            }
        }
    }
}

void engineUI::configureNextWindowPosSize(ImVec2 position, ImVec2 size) {
    ImGui::SetNextWindowPos(position, ImGuiCond_Once);
    ImGui::SetNextWindowSize(size, ImGuiCond_Once);
}

void engineUI::initIcons() {
    ICONS = new std::map<std::string, Texture> {
        {"folderClosed", Texture(R"(Assets\icons\folder-solid.png)")},
        {"folderOpen", Texture(R"(Assets\icons\folder-open-regular.png)")},
        {"object", Texture(R"(Assets\icons\cube-solid.png)")}
    };
}

void engineUI::EditWindow::drawVec3Input(const std::string &inputName, glm::vec3 &vector3) {
    ImGui::Separator();
    ImGui::Text((inputName + ":").c_str());
    glm::vec3 vec3Buffer = vector3;
    if (ImGui::DragFloat3(("##" + inputName).c_str(), glm::value_ptr(vector3), 0.005f)) {

    }
}

std::string engineUI::EditWindow::drawTextInput(const std::string &inputName, std::string &text) {
    ImGui::Separator();
    ImGui::Text((inputName + ":").c_str());

    char buffer[256];
    strcpy(buffer, text.c_str());

    if (ImGui::InputText(("##" + inputName).c_str(), buffer, 256)) {
        text = buffer;
    }

    return text;
}

void engineUI::EditWindow::drawGameObjectButton(std::vector<GameObject*> &gameObjects) {
    for (auto& object : gameObjects) {
        ImGui::Image((void*)(intptr_t)ICONS->find("object")->second.id, ImVec2(20, 20), ImVec2(0, 1), ImVec2(1, 0));
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

void engineUI::EditWindow::objectEditDraw() {
    ImGui::Begin("Object Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("This is the object editor window!");

    selectedObject->name = drawTextInput("Object Name", selectedObject->name);

    drawVec3Input("Object Position", selectedObject->transform.position);
    drawVec3Input("Object Rotation", selectedObject->transform.rotation);
    drawVec3Input("Object Scale", selectedObject->transform.scale);

    ImGui::Separator();
    ImGui::Text("Attached Scripts:");
    for (int i = 0; i < selectedObject->scripts.size(); ++i) {
        ImGui::Text(selectedObject->scripts[i]->path.filename().string().c_str());
        ImGui::SameLine();
        if (ImGui::Button("Delete")) {
            selectedObject->scripts.erase(selectedObject->scripts.begin() + i);
        }
    }

    ImGui::Button("Drop New Script Here", ImVec2(320, 50));
    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_SCRIPT_FILE")) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_NotAllowed);
            ImGui::BeginTooltip();
            ImGui::Text("Drop Script here to add to game object");
            ImGui::EndTooltip();
            selectedObject->scripts.push_back(new Script(static_cast<char*>(payload->Data), selectedObject)); // turn the void pointer to string :)
        }
        ImGui::EndDragDropTarget();
    }

    ImGui::End();
}

void engineUI::EditWindow::brushEditDraw() {
    ImGui::Begin("Brush Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("This is the brush editor window!");

    ImGui::Separator();
    ImGui::Checkbox("Snapping enabled for this brush", &selectedBrush->isSnapEnabled);


    ImGui::Separator();
    if (selectedBrush->isSnapEnabled) {
        ImGui::Text("Brush Position:");
        if (ImGui::DragFloat3("##Brush Position", glm::value_ptr(selectedBrush->transform.position), 1.0f)) {
        }
    } else {
        drawVec3Input("Brush Position", selectedBrush->transform.position); // normal drag
    }
    drawVec3Input("Brush Rotation", selectedBrush->transform.rotation);

    ImGui::Separator();
    if (selectedBrush->isSnapEnabled) {
        ImGui::Text("Brush Scale:");
        if (ImGui::DragFloat3("##Brush Scale", glm::value_ptr(selectedBrush->transform.scale), 1.0f)) {
        }
    } else {
        drawVec3Input("Brush Scale", selectedBrush->transform.scale); // normal drag
    }

    if (selectedBrush->isSnapEnabled) {
        selectedBrush->snapToWholeVerts();
    }

    ImGui::End();
}

void engineUI::EditWindow::setSelected(GameObject *gameObject) {
    if (selectedBrush != nullptr) {
        selectedBrush = nullptr;
    }
    this->selectedObject = gameObject;
}

void engineUI::EditWindow::setSelected(Brush *brush) {
    if (selectedObject != nullptr) {
        selectedObject = nullptr;
    }
    this->selectedBrush = brush;
}

void engineUI::EditWindow::draw() {
    configureNextWindowPosSize(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 0),
                               ImVec2(320, 300));
    ImGui::Begin("Game Object Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("Game Object Editor");
    ImGui::SameLine();
    if (ImGui::Button("Save Map")) {
        engine->map.save();
    }

    ImGui::Separator();

    if (ImGui::TreeNode("Map Geometry")) {

        ImGui::TreePop();
    }
    if (ImGui::BeginPopupContextWindow()) {
        if (ImGui::MenuItem("Add Cube Brush")) {
            engine->map.brushList.push_back(new Brush());
        }
        ImGui::EndPopup();
    }
    if (ImGui::TreeNode("Game Objects")) {
        drawGameObjectButton(engine->map.gameObjects);
        ImGui::TreePop();
    }

    ImGui::End();

    configureNextWindowPosSize(ImVec2(ImGui::GetIO().DisplaySize.x - 320, 300),
                               ImVec2(320, 300));
    if (selectedObject != nullptr) {
        objectEditDraw();
    } else if (selectedBrush != nullptr) {
        brushEditDraw();
    }
}

void engineUI::EditWindow::clearSelected() {
    selectedObject = nullptr;
    selectedBrush = nullptr;
}
