//
// Created by kirut on 9/3/2023.
//

#ifndef PROJECTBAHAMUT_WINDOW_H
#define PROJECTBAHAMUT_WINDOW_H

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

bool quit = false;
int winWidth;
int winHeight;

SDL_DisplayMode displayMode;
SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_GLContext glContext = nullptr;
SDL_Event e;

int main(int argc, char *argv[]);
int initWindow();
void windowEvents();


#endif //PROJECTBAHAMUT_WINDOW_H
