//
// Created by kirut on 10/9/2023.
//

#ifndef PROJECTBAHAMUT_GAMEOBJECT_H
#define PROJECTBAHAMUT_GAMEOBJECT_H


#include <string>
#include "Model.h"
#include "Transformation.h"
#include "Camera.h"
#include "Script.h"

class Script;

class GameObject : public Model {
public:
    std::string name;
    std::vector<Script*> scripts;
    std::vector<GameObject*> nestedGameObjects; // gameobject is a node in a tree

    // GameObject(); TODO: make default
    GameObject(std::string name, const std::string& modelPath);
    GameObject(std::string name, const std::string& modelPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void draw(Shader &shader) override;
};


#endif //PROJECTBAHAMUT_GAMEOBJECT_H
