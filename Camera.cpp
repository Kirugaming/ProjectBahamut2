//
// Created by kirut on 10/10/2023.
//
#include <iostream>
#include "Camera.h"

Camera::Camera(glm::vec3 inPosition, glm::vec3 up) : direction(glm::vec3(0.0f, 0.0f, -1.0f)) {
    position = inPosition;
    worldUp = up;

    yaw = -90.0f;
    pitch = 0.0f;
    updateCameraVectors();
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(position, position + direction, up);
}

void Camera::movement(Camera::Input moveDirection, float deltaTime) {
    std::cout << deltaTime << std::endl;
    float velocity = 2.5f * deltaTime;
    switch (moveDirection) {
        case FORWARD:
            position += direction * velocity;
            break;
        case BACKWARD:
            position -= direction * velocity;
            break;
        case LEFT:
            position -= right * velocity;
            break;
        case RIGHT:
            position += right * velocity;
            break;
    }
}

void Camera::mouseLook(float mouseX, float mouseY) {
    yaw += mouseX * .1;
    pitch += mouseY * .1;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    } else if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    updateCameraVectors();
}

void Camera::setPitch(float offset) {
    pitch += offset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    updateCameraVectors();
}

void Camera::setYaw(float offset) {
    yaw += offset;

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(direction, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, direction));
}
