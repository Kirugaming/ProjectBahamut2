//
// Created by kirut on 7/23/2024.
//

#ifndef PROJECTBAHAMUT_MAPEXPLORERWINDOW_H
#define PROJECTBAHAMUT_MAPEXPLORERWINDOW_H


#include "BaseImGuiWindow.h"

class MapExplorerWindow : public BaseImGuiWindow {
    GameObject *selectedObject = nullptr;
    Brush *selectedBrush = nullptr;

    void objectEditDraw();
    void brushEditDraw();
    static void drawVec3Input(const std::string& inputName, glm::vec3 &vector3);
    static std::string drawTextInput(const std::string& inputName, std::string &text);
    void drawGameObjectButton(std::vector<GameObject*> &gameObjects);

    void setSelected(GameObject *gameObject);
    void setSelected(Brush *brush);
    void clearSelected();

protected:
    void draw() override;
    
public:
    MapExplorerWindow();
};


#endif //PROJECTBAHAMUT_MAPEXPLORERWINDOW_H
