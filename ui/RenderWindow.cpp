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
    pollEvents();

    // Get the global mouse position
    ImVec2 mousePos = ImGui::GetMousePos();

    // Get the position of the current viewport
    ImVec2 viewportPos = ImGui::GetWindowViewport()->Pos;

    // Calculate the relative mouse position within the window
    // This is manual offset until i figure why its so off without it
    ImVec2 mouseRelative = ImVec2(mousePos.x, size.height - mousePos.y + 30);


    ImGui::Begin("Test");
    ImGui::Text("Mouse Position Relative: (%.1f, %.1f)", mouseRelative.x, mouseRelative.y);
    ImGui::End();

    ImGui::ShowDemoWindow();

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    engine->draw();
    ImGui::Image((void*)(intptr_t) renderTextureId, ImGui::GetContentRegionAvail());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::SetCursorPos(ImVec2(0,0)); // puts it over last element
    if (ImGui::InvisibleButton("RenderWindowButton", ImVec2(size.width, size.height))) {
        engine->createRay({ // normalize
          (2.0f * mouseRelative.x) / size.width - 1.0f,
          1.0f - (2.0f * mouseRelative.y) / size.height,
          1.0f
        });
    }


    ImGui::End();
}

void RenderWindow::createFrameBuffer() {
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // create the texture that the renderer will draw on and attach it to FBO and make sure the FBO is complete
    glGenTextures(1, &renderTextureId);
    glBindTexture(GL_TEXTURE_2D, renderTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.width, size.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTextureId, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cerr << "RENDER WINDOW FRAMEBUFFER IS MISSING ATTACHMENTS" << std::endl;
        throw std::exception();
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderWindow::pollEvents() {
    if (hasBeenResized()) {
        createFrameBuffer();
        engine->setAspectRatio(size.width / size.height);
    }
}
