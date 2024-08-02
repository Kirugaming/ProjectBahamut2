//
// Created by kirut on 7/22/2024.
//

#ifndef PROJECTBAHAMUT_DOCKSPACEWINDOW_H
#define PROJECTBAHAMUT_DOCKSPACEWINDOW_H


#include "BaseImGuiWindow.h"

// Main ImGui Window that holds the other imgui windows
class DockspaceWindow : BaseImGuiWindow {
    ImGuiID dockspaceID;
    std::vector<BaseImGuiWindow*> windows;
    bool firstFrame = true;

    void setDockspace();

public:
    DockspaceWindow();

    void draw() override;
};


#endif //PROJECTBAHAMUT_DOCKSPACEWINDOW_H
