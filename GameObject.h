//
// Created by kirut on 10/9/2023.
//

#ifndef PROJECTBAHAMUT_GAMEOBJECT_H
#define PROJECTBAHAMUT_GAMEOBJECT_H


#include <string>
#include "Model.h"
#include "Transformation.h"

class GameObject {
public:
    std::string name;
    Model model;
    Transform transform;

    Shader shader;

    // GameObject(); TODO: make default
    GameObject(std::string name, Model model);

    void draw();
};


#endif //PROJECTBAHAMUT_GAMEOBJECT_H
