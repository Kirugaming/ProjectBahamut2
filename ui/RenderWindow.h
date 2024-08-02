//
// Created by kirut on 7/13/2024.
//

#ifndef PROJECTBAHAMUT_RENDERWINDOW_H
#define PROJECTBAHAMUT_RENDERWINDOW_H

#include "BaseImGuiWindow.h"

class RenderWindow : public BaseImGuiWindow {
    unsigned int FBO{};
    unsigned int renderTextureId{};
    bool firstFrame = true;

    void handleResizing();
    void mouseRelativeToRender();

protected:
    void draw() override;

public:
    explicit RenderWindow();

    float getAspectRatio() const;
};


#endif //PROJECTBAHAMUT_RENDERWINDOW_H
