//
// Created by kirut on 7/22/2024.
//

#include "BaseImGuiWindow.h"

Engine* BaseImGuiWindow::engine;
ImGuiViewport* BaseImGuiWindow::viewport;

BaseImGuiWindow::BaseImGuiWindow() {
    if (!imguiStarted) {
        std::cerr << "ImGui has not started yet! Please call startImGui before creating an imgui window." << std::endl;
        throw std::exception();
    }
}

void BaseImGuiWindow::startImGui(SDL_Window *sdlWindow, SDL_GLContext glContext) {
    if (!imguiStarted) {
        // projects needs own imgui context for its own sdl window

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
        io.ConfigDockingWithShift = true;

        ImGui_ImplSDL2_InitForOpenGL(sdlWindow, glContext);
        ImGui_ImplOpenGL3_Init();

        viewport = ImGui::GetMainViewport();

        imguiStarted = true;
    } else {
        std::cerr << "ImGui has already started" << std::endl;
        throw std::exception();
    }
}

void BaseImGuiWindow::shutdownImGui() {
    if (imguiStarted) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        imguiStarted = false;
    } else {
        std::cerr << "ImGui has not started yet! Please call startImGui before wanting to destroy the current imgui context." << std::endl;
        throw std::exception();
    }
}
