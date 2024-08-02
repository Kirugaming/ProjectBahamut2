//
// Created by kirut on 7/22/2024.
//

#include "DockspaceWindow.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "RenderWindow.h"
#include "MapExplorerWindow.h"
#include "backends/imgui_impl_sdl2.h"
#include "ProjectExplorerWindow.h"

DockspaceWindow::DockspaceWindow() {

    windows.push_back(new RenderWindow());
    windows.push_back(new MapExplorerWindow());

    DockspaceWindow::draw();
}

void DockspaceWindow::setDockspace() {
    ImGui::DockBuilderRemoveNode(dockspaceID); // imgui saves window info and it may be saved so reset to default (for now?)
    ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->WorkSize);
    ImGui::DockBuilderSetNodePos(dockspaceID, viewport->WorkPos);

    ImGuiID projectExplorerSpaceID = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left, 0.10f, nullptr, &dockspaceID);
    ImGuiID objectEditorSpaceID = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Right, 0.15f, nullptr, &dockspaceID);

    // This is where you say which windows go where in the dockspace
    ImGui::DockBuilderDockWindow("Dockspace", dockspaceID);
    ImGui::DockBuilderDockWindow("RenderWindow", dockspaceID);
    ImGui::DockBuilderDockWindow("ProjectExplorer", projectExplorerSpaceID);
    ImGui::DockBuilderDockWindow("MapExplorer", objectEditorSpaceID);

    ImGui::DockBuilderFinish(dockspaceID);
}

void DockspaceWindow::draw() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    dockspaceID = ImGui::GetID("Dockspace");
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::Begin("Dockspace", reinterpret_cast<bool *>(quit),
                 ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize
                 | ImGuiWindowFlags_NoMove| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus);
    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_AutoHideTabBar);

    for (auto window : windows) {
        window->draw();
    }

    if (firstFrame) {
        setDockspace();
        firstFrame = false;
    }

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // multiple viewport
    SDL_Window* currentWindow = SDL_GL_GetCurrentWindow();
    SDL_GLContext currentContext = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(currentWindow, currentContext);
}
