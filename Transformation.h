//
// Created by kirut on 10/9/2023.
//

#ifndef PROJECTBAHAMUT_TRANSFORMATION_H
#define PROJECTBAHAMUT_TRANSFORMATION_H


#include "glm/vec3.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/fwd.hpp"

struct Transform {
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale;

    Transform(const glm::vec3 &position, const glm::quat &rotation, const glm::vec3 &scale) : position(position),
                                                                                              rotation(rotation),
                                                                                              scale(scale) {};
    Transform() : Transform(glm::vec3(0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f)) {};

    glm::mat4 toMat4() const;
};



#endif //PROJECTBAHAMUT_TRANSFORMATION_H
