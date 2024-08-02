//
// Created by kirut on 7/13/2024.
//

#ifndef PROJECTBAHAMUT_BASEWINDOW_H
#define PROJECTBAHAMUT_BASEWINDOW_H


#include "../engine/Engine.h"

struct WinSize {
    int height;
    int width;
};

class BaseWindow {

protected:
    bool quit = false;

    virtual void draw() = 0;
};


#endif //PROJECTBAHAMUT_BASEWINDOW_H
