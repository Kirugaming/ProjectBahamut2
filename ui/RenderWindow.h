//
// Created by kirut on 7/13/2024.
//

#ifndef PROJECTBAHAMUT_RENDERWINDOW_H
#define PROJECTBAHAMUT_RENDERWINDOW_H

#include "BaseImGuiWindow.h"

class RenderWindow : public BaseImGuiWindow {
    unsigned int FBO{};
    unsigned int renderTextureId{};

    void pollEvents();

protected:
    void draw() override;
    void createFrameBuffer();
public:
    explicit RenderWindow();

};


#endif //PROJECTBAHAMUT_RENDERWINDOW_H
