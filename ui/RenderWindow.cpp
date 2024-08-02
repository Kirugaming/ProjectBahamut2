//
// Created by kirut on 7/13/2024.
//

#include "RenderWindow.h"

RenderWindow::RenderWindow() {
    winFlags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav;

    engine = new Engine();
}

void RenderWindow::draw() {
    ImGui::Begin("RenderWindow", reinterpret_cast<bool *>(quit), winFlags);

    ImVec2 winSize = ImGui::GetContentRegionAvail();
    engine->setAspectRatio(winSize.x / winSize.y);
    // framebuffer image setup here so i can get information of the win ^
    if (firstFrame) {
        // init render texturee
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // create the texture that the renderer will draw on and attach it to FBO and make sure the FBO is complete
        glGenTextures(1, &renderTextureId);
        glBindTexture(GL_TEXTURE_2D, renderTextureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, winSize.x, winSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTextureId, 0);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cerr << "RENDER WINDOW FRAMEBUFFER IS MISSING ATTACHMENTS" << std::endl;
            throw std::exception();
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        firstFrame = false;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    engine->draw();
    ImGui::Image((void*)(intptr_t) renderTextureId, ImGui::GetContentRegionAvail());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::End();
}
