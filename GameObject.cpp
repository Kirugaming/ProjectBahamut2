//
// Created by kirut on 10/9/2023.
//

#include "GameObject.h"

#include <utility>


GameObject::GameObject(std::string name, const std::string& modelPath) : shader(), name(std::move(name)),  model(*new Model(modelPath.c_str())){
    transform = Transform();
}

GameObject::GameObject(std::string name, const std::string &modelPath, glm::vec3 position, glm::vec3 rotation,
                       glm::vec3 scale) : shader(), name(std::move(name)),  model(*new Model(modelPath.c_str())) {
    transform = Transform();
    transform.position = position;
    transform.rotation = glm::angleAxis(glm::radians(90.0f), rotation);
    transform.scale = scale;
}

void GameObject::draw(glm::mat4 cameraView) {
    shader.use();

    // apply transformations
    this->shader.editShaderWithMat4("view", cameraView);
    this->shader.editShaderWithMat4("perspective", glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f));
    this->shader.editShaderWithMat4("model", transform.toMat4());

    model.draw(shader);

    shader.unUse();
}
