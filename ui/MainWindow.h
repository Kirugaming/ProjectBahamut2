//
// Created by kirut on 7/21/2024.
//

#ifndef PROJECTBAHAMUT_MAINWINDOW_H
#define PROJECTBAHAMUT_MAINWINDOW_H


#include "backends/imgui_impl_opengl3.h"
#include "DockspaceWindow.h"
#include "BaseSDLWindow.h"

// The SDL Window
class MainWindow : BaseSDLWindow {
    DockspaceWindow* imGuiWindow;

    void draw() override;
    void KeyboardInput();

public:
    MainWindow();
    ~MainWindow();
};


#endif //PROJECTBAHAMUT_MAINWINDOW_H
