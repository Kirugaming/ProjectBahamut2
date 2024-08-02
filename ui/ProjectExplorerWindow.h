//
// Created by kirut on 7/23/2024.
//

#ifndef PROJECTBAHAMUT_PROJECTEXPLORERWINDOW_H
#define PROJECTBAHAMUT_PROJECTEXPLORERWINDOW_H


#include "BaseImGuiWindow.h"

struct Project {
    std::string name;
    std::string path;
    // version
    // last modified
};

class ProjectExplorerWindow : public BaseImGuiWindow {
    std::unordered_set<std::string> openFolders;
    std::string *fileDragTemp = nullptr;
    Project project;
    bool projectSelected = false;

    void draw() override;
    void projectChooser();
    void displayFileTree(const std::string &path, int level);
    void handleFileTypes(const std::filesystem::directory_entry& file);
public:
    ProjectExplorerWindow();
};


#endif //PROJECTBAHAMUT_PROJECTEXPLORERWINDOW_H
