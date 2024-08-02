//
// Created by kirut on 7/23/2024.
//

#include "MapExplorerWindow.h"

MapExplorerWindow::MapExplorerWindow() {

}

void MapExplorerWindow::draw() {
    ImGui::Begin("MapExplorer", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoCollapse);

    ImGui::Text("Game Object Editor");

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

    if (selectedObject != nullptr) {
        objectEditDraw();
    } else if (selectedBrush != nullptr) {
        brushEditDraw();
    }
}

void MapExplorerWindow::objectEditDraw() {
    ImGui::Begin("Object edit", reinterpret_cast<bool *>(true));
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

void MapExplorerWindow::brushEditDraw() {
    ImGui::Begin("Brush Editor", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoTitleBar);
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

void MapExplorerWindow::drawVec3Input(const std::string &inputName, glm::vec3 &vector3) {
    ImGui::Separator();
    ImGui::Text((inputName + ":").c_str());
    glm::vec3 vec3Buffer = vector3;
    if (ImGui::DragFloat3(("##" + inputName).c_str(), glm::value_ptr(vector3), 0.005f)) {

    }
}

std::string MapExplorerWindow::drawTextInput(const std::string &inputName, std::string &text) {
    ImGui::Separator();
    ImGui::Text((inputName + ":").c_str());

    char buffer[256];
    strcpy(buffer, text.c_str());

    if (ImGui::InputText(("##" + inputName).c_str(), buffer, 256)) {
        text = buffer;
    }

    return text;
}

void MapExplorerWindow::drawGameObjectButton(std::vector<GameObject *> &gameObjects) {
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

void MapExplorerWindow::setSelected(GameObject *gameObject) {
    if (selectedBrush != nullptr) {
        selectedBrush = nullptr;
    }
    this->selectedObject = gameObject;
}

void MapExplorerWindow::setSelected(Brush *brush) {
    if (selectedObject != nullptr) {
        selectedObject = nullptr;
    }
    this->selectedBrush = brush;
}
