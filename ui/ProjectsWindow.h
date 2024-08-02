//
// Created by kirut on 7/24/2024.
//

#ifndef PROJECTBAHAMUT_PROJECTSWINDOW_H
#define PROJECTBAHAMUT_PROJECTSWINDOW_H

#include "BaseImGuiWindow.h"
#include <yaml-cpp/yaml.h>

struct Project {
    std::string name;
    std::string path;
    // version
    // last modified
};

class ProjectsWindow : BaseImGuiWindow {
    std::vector<Project> projectList;
    bool isMakeNewProjectOpen = false;
    Project* newProject = nullptr;


    void openProjectsFile();
    void newProjectWindow();
    void appendNewProject();
public:
    Project selectedProject;

    ProjectsWindow();
    ~ProjectsWindow();
    void draw() override;
};




#endif //PROJECTBAHAMUT_PROJECTSWINDOW_H
