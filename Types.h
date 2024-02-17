//
// Created by kirut on 2/16/2024.
//

#ifndef PROJECTBAHAMUT_TYPES_H
#define PROJECTBAHAMUT_TYPES_H

#include <stdexcept>
#include "imgui.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/detail/type_mat4x4.hpp"

typedef struct vec2 {
    float x, y;

    vec2(float inX, float inY) : x(inX), y(inY) {};
    explicit vec2(float value) : vec2(value, value) {};
    vec2() : vec2(0.0f) {};
    explicit vec2(ImVec2 imVec2) : x(imVec2.x), y(imVec2.y) {};
    explicit vec2(glm::vec2 glmVec2) : x(glmVec2.x), y(glmVec2.y) {};

    [[nodiscard]] float* toPointer() {
        return &x;
    }

    const float &operator[](int index) const {
        switch (index) {
            case 0: x;
            case 1: y;
            default: throw std::out_of_range("Vec2::Index out of range");
        }
    }
    explicit operator ImVec2() const {
        return {x, y};
    }
    explicit operator glm::vec2() const {
        return {x, y};
    }
} vec2;

typedef struct vec4 {
    float x, y, z, w;

    vec4(float inX, float inY, float inZ, float inW) : x(inX), y(inY), z(inZ), w(inW) {};
    explicit vec4(float value) : vec4(value, value, value, value) {};
    vec4() : vec4(0.0f) {};
    explicit vec4(ImVec4 imVec4) : x(imVec4.x), y(imVec4.y), z(imVec4.z), w(imVec4.w) {};
    explicit vec4(glm::vec4 glmVec4) : x(glmVec4.x), y(glmVec4.y), z(glmVec4.z), w(glmVec4.w) {};

    [[nodiscard]] float* toPointer() {
        return &x;
    }

    float &operator[](int index) {
        switch (index) {
            case 0: x;
            case 1: y;
            case 2: z;
            case 3: w;
            default: throw std::out_of_range("Vec4::Index out of range");
        }
    }
    const float &operator[](int index) const {
        switch (index) {
            case 0: x;
            case 1: y;
            case 2: z;
            case 3: w;
            default: throw std::out_of_range("Vec4::Index out of range");
        }
    }
    explicit operator ImVec4() const {
        return {x, y, z, w};
    }
    explicit operator glm::vec4() const {
        return {x, y, z, w};
    }

} vec4;

typedef struct Transform {
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Transform() : position(0.0f), rotation(0.0f), scale(0.0f) {};
    Transform(glm::vec3 inPosition, glm::vec3 inRotation, glm::vec3 inScale) : position(inPosition), rotation(inRotation), scale(inScale) {};

    [[nodiscard]] glm::mat4 toMat4() const;
} Transform;

#endif //PROJECTBAHAMUT_TYPES_H
