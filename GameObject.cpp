//
// Created by kirut on 10/9/2023.
//

#include "GameObject.h"

#include <utility>


GameObject::GameObject(std::string name, Model model) : shader(), name(std::move(name)), model(std::move(model)) {
    transform = Transform();
}

void GameObject::draw() {
    shader.use();

    this->shader.editShaderWithMat4("model", transform.toMat4());

    model.draw(shader);

    //shader.unUse();
}
