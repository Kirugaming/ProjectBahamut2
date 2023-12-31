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

class GameObject {
public:
    std::string name;
    Model model;
    Transform transform;

    Shader shader;
    std::vector<Script*> scripts;

    // gameobject is a node in a tree
    std::vector<GameObject*> nestedGameObjects;

    // GameObject(); TODO: make default
    GameObject(std::string name, const std::string& modelPath);
    GameObject(std::string name, const std::string& modelPath, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    void draw();

    void draw(Camera camera);

    void draw(glm::mat4 cameraView);
};


#endif //PROJECTBAHAMUT_GAMEOBJECT_H
