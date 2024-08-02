//
// Created by kirut on 7/13/2024.
//

#ifndef PROJECTBAHAMUT_BASEWINDOW_H
#define PROJECTBAHAMUT_BASEWINDOW_H


#include "../engine/Engine.h"

struct WinSize {
    float width;
    float height;
};

class BaseWindow {

protected:
    bool quit = false;
    WinSize size = WinSize(0,0);

    virtual void draw() = 0;
};


#endif //PROJECTBAHAMUT_BASEWINDOW_H
