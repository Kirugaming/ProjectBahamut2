//
// Created by kirut on 7/24/2024.
//

#include "ProjectsWindow.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_sdl2.h"
#include "BaseImGuiWindow.h"

ProjectsWindow::ProjectsWindow() {
    openProjectsFile();
    ProjectsWindow::draw();
}

void ProjectsWindow::draw() {
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::Begin("Projects Window", reinterpret_cast<bool *>(quit),
                 ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
                 | ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);
    ImGui::Text("Available Projects:");
    ImGui::SameLine(viewport->WorkSize.x-90);
    if (ImGui::Button("New Project")) {
        isMakeNewProjectOpen = true;
        newProject = new Project;
    }

    for (Project& project : projectList) {
        if (ImGui::Button((project.name + "\n" + project.path).c_str())) {
            selectedProject = project;
            quit = true;
        }
    }

    if (isMakeNewProjectOpen) {
        newProjectWindow();
    }

    ImGui::End();
}

void ProjectsWindow::openProjectsFile() {
    std::ifstream file("projects.yaml");
    if (!file.good()) {
        return; // no projects have been created
    } else {
        YAML::Node projectsNode = YAML::LoadFile("projects.yaml");

        for (auto project : projectsNode["Projects"]) {
            projectList.emplace_back(project["name"].as<std::string>(), project["path"].as<std::string>());
        }
    }
}

void ProjectsWindow::newProjectWindow() {
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::Begin("Project Creation", &isMakeNewProjectOpen, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );

    char nameBuffer[256];
    strcpy(nameBuffer, newProject->name.c_str());
    if (ImGui::InputText("Project Name", nameBuffer, 256)) {
        newProject->name = nameBuffer;
    }
    char pathBuffer[256];
    strcpy(pathBuffer, newProject->path.c_str());
    if (ImGui::InputText("Project Path", pathBuffer, 256)) {
        newProject->path = pathBuffer;
    }
    if (ImGui::Button("Create")) {
        projectList.push_back(*newProject);
        appendNewProject();
        isMakeNewProjectOpen = false;
    }

    ImGui::End();
}

void ProjectsWindow::appendNewProject() {
    YAML::Node projectListNode;

    for (Project project : projectList) {
        YAML::Node newProjectNode;
        newProjectNode["name"] = project.name;
        newProjectNode["path"] = project.path;

        projectListNode["Projects"].push_back(newProjectNode);
    }

    std::ofstream file("projects.yaml");
    file << projectListNode;
}
