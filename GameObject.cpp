//
// Created by kirut on 10/9/2023.
//

#include "GameObject.h"

#include <utility>


GameObject::GameObject(std::string name, const std::string& modelPath) : name(std::move(name)),  Model(*new Model(modelPath.c_str())) {
}

GameObject::GameObject(std::string name, const std::string &modelPath, glm::vec3 position, glm::vec3 rotation,
                       glm::vec3 scale) : name(std::move(name)),  Model(*new Model(modelPath.c_str())) {
    transform.position = position;
    transform.rotation = rotation;
    transform.scale = scale;
}

void GameObject::draw(Shader &shader) {
    Model::draw(shader);
}
