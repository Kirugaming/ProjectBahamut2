//
// Created by kirut on 10/9/2023.
//

#include "Transformation.h"

glm::mat4 Transform::toMat4() const {
    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), position);

    auto rotationMat = glm::mat4(1.0f);
    rotationMat = glm::rotate(rotationMat, rotation.x, glm::vec3(1, 0, 0));
    rotationMat = glm::rotate(rotationMat, rotation.y, glm::vec3(0, 1, 0));
    rotationMat = glm::rotate(rotationMat, rotation.z, glm::vec3(0, 0, 1));

    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);

    return translationMat * rotationMat * scaleMat;
}
