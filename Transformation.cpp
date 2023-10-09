//
// Created by kirut on 10/9/2023.
//

#include "Transformation.h"

glm::mat4 Transform::toMat4() const {
    glm::vec3 x = this->rotation * glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 y = this->rotation * glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 z = this->rotation * glm::vec3(0.0f, 0.0f, 1.0f);
    // scale
    x *= this->scale.x;
    y *= this->scale.y;
    z *= this->scale.z;
    // translation
    glm::vec3 p = this->position;
    // create matrix
    return {x.x, x.y, x.z, 0.0f,
            y.x, y.y, y.z, 0.0f,
            z.x, z.y, z.z, 0.0f,
            p.x, p.y, p.z, 1.0f};
}
