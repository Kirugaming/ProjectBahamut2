//
// Created by kirut on 9/3/2023.
//

#include "main.h"
#include "GameObject.h"


// SDL Rendering is for Engine UI,
// OpenGL is for game rendering and game ui and what not

int main(int argc, char *argv[]) {
    Engine engine;
    engine.engineLoop();

    return 0;
}