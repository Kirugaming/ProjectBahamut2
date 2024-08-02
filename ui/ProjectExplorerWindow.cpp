//
// Created by kirut on 7/23/2024.
//

#include "ProjectExplorerWindow.h"

ProjectExplorerWindow::ProjectExplorerWindow() {

}

void ProjectExplorerWindow::draw() {
    ImGui::Begin("ProjectExplorer", reinterpret_cast<bool *>(quit));
    {
        if (projectSelected) {
            ImGui::Text("Project Explorer");
            ImGui::Separator();

//        displayFileTree(project.path, 0);


        } else {
//            projectChooser();
        }
    }
    ImGui::End();

}

void ProjectExplorerWindow::displayFileTree(const std::string &path, int level) {
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

void ProjectExplorerWindow::handleFileTypes(const std::filesystem::directory_entry &file) {
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
                engine->map = *new Map(file.path().string());
            }
        }
    }
}

//void ProjectExplorerWindow::projectChooser() {
//    ImGui::Text("Available Projects:");
//    ImGui::SameLine(viewport->WorkSize.x-90);
//    if (ImGui::Button("New Project")) {
//        isMakeNewProjectOpen = true;
//        newProject = new Project;
//    }
//
//    for (Project& project : projectList) {
//        if (ImGui::Button((project.name + "\n" + project.path).c_str())) {
//            selectedProject = project;
//            quit = true;
//        }
//    }
//
//    if (isMakeNewProjectOpen) {
//        newProjectWindow();
//    }
//}
