//
// Created by kirut on 10/10/2023.
//

#ifndef PROJECTBAHAMUT_CAMERA_H
#define PROJECTBAHAMUT_CAMERA_H

#include "glm/vec3.hpp"
#include "glm/geometric.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

class Camera {
public:
    enum Input {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 worldUp;
    glm::vec3 right;

    float yaw;
    float pitch;


    Camera(glm::vec3 inPosition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 getView() const;
    void movement(Input direction, float deltaTime);
    void mouseLook(float mouseX, float mouseY);

private:
    void updateCameraVectors();
};


#endif //PROJECTBAHAMUT_CAMERA_H
