//
// Created by kirut on 9/3/2023.
//

#include "main.h"
#include "GameObject.h"
#include "Projects.h"


// SDL Rendering is for Engine UI,
// OpenGL is for game rendering and game ui and what not

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL FAILED TO INITIALIZE!\n " << SDL_GetError() << std::endl;
        return -1;
    }

    ProjectsWindow projects;
    projects.renderLoop();
    if (projects.selectedProject == nullptr) {
        return 0; // closed without selecting anything
    }
    Project chosenProject = *projects.selectedProject;

    //delete &projects;

    Engine engine(chosenProject);
    engineUI ui(engine.window, engine.glContext);

    engine.ui = &ui; // ui and engine need to know stuff from each other
    ui.engine = &engine;

    engine.engineLoop();

    return 0;
}