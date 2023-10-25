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
    Project chosenProject = *projects.selectedProject;
    //delete &projects;

    Engine engine(chosenProject);
    engine.engineLoop();

    return 0;
}