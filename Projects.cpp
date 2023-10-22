//
// Created by kirut on 10/21/2023.
//

#include <fstream>
#include <utility>
#include "Projects.h"

ProjectsWindow::ProjectsWindow() {

    window = SDL_CreateWindow("ProjectBahamut Projects", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 400,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    openProjectFile();
}

void ProjectsWindow::renderLoop() {
    while (!quit) {
        while( SDL_PollEvent( &event ) ) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        if (isMakeNewProjectOpen) {
            makeNewProject();
        }

        ImGui::Begin("Project Select");
        if (ImGui::Button("New Project")) {
            newProject = new Project("", "");
            isMakeNewProjectOpen = true;
        }
        ImGui::Separator();
        ImGui::Text("Existing Projects: ");
        for (const Project& project : projectList) {
            if (ImGui::Button((project.name + "\n" + project.path).c_str())) {

            }
        }

        ImGui::End();

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ProjectsWindow::makeNewProject() {
    ImGui::Begin("Project Creation");

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

void ProjectsWindow::openProjectFile() {
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

Project::Project(std::string inName, std::string inPath)  : name(std::move(inName)), path(std::move(inPath)) {

}
