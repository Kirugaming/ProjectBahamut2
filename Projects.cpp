//
// Created by kirut on 10/21/2023.
//

#include <fstream>
#include <utility>
#include "Projects.h"

ProjectsWindow::ProjectsWindow() {
    // initializes rendering
    window = SDL_CreateWindow("ProjectBahamut Projects", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 400,
                              SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);

    // ui
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
        // events
        while( SDL_PollEvent( &event ) ) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }

        // ui render
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        renderUi();

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

ProjectsWindow::~ProjectsWindow() {

}

void ProjectsWindow::renderUi() {
    ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("Project Select", reinterpret_cast<bool *>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    if (ImGui::Button("New Project")) {
        newProject = new Project("", "");
        isMakeNewProjectOpen = true;
    }
    ImGui::Separator();
    ImGui::Text("Existing Projects: ");
    for (Project &project : projectList) {
        if (ImGui::Button((project.name + "\n" + project.path).c_str())) {
            selectedProject = &project;
            quit = true;
        }
    }

    if (isMakeNewProjectOpen) {
        ImGui::SetWindowFocus("Project Creation"); // keeps window from going behind main window
        makeNewProject();
    }

    ImGui::End();
}

Project::Project(std::string inName, std::string inPath)  : name(std::move(inName)), path(std::move(inPath)) {

}
