//
// Created by kirut on 12/18/2023.
//

#ifndef PROJECTBAHAMUT_BRUSH_H
#define PROJECTBAHAMUT_BRUSH_H

#include <vector>
#include "Transformation.h"
#include "Shader.h"

enum BrushShapes {
    CUBE = 0,
//    CYLINDER = 1
};

struct Cube {
    std::vector<float> vertices = { // normal array gets angwy
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f
    };
};

class Brush {
    Shader shader;
    Transform transform;
    unsigned int VAO{}, VBO{}, EBO{};
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

public:
    explicit Brush(BrushShapes shape);

    void draw(glm::mat4 cameraView) const;


};


#endif //PROJECTBAHAMUT_BRUSH_H
