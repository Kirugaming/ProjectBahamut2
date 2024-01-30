//
// Created by kirut on 12/18/2023.
//

#ifndef PROJECTBAHAMUT_BRUSH_H
#define PROJECTBAHAMUT_BRUSH_H

#include <vector>
#include "Transformation.h"
#include "Shader.h"
#include "Mesh.h"
#include "yaml-cpp/node/node.h"

enum BrushShapes {
    CUBE = 0,
//    CYLINDER = 1
};

static struct Cube {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    Cube() {
        vertices = {// Position | Normal | Texture Coordinate
                {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)},

                {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 0.0f)},
                {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 0.0f)},
                {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(1.0f, 1.0f)},
                {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec2(0.0f, 1.0f)}
        };
        indices =  {
                0, 1, 2,
                2, 3, 0,

                1, 5, 6,
                6, 2, 1,

                5, 4, 7,
                7, 6, 5,

                4, 0, 3,
                3, 7, 4,

                0, 1, 5,
                5, 4, 0,

                3, 2, 6,
                6, 7, 3
        };
    }
} cube;

class Brush : public Mesh {

public:
    int id;
    Transform transform;
    bool isSnapEnabled = true;

    Brush();
    Brush(std::vector<Vertex> &inVertices, std::vector<unsigned int> &inIndices, Transform &inTransform);
    Brush(int id, Transform transform1);

    void draw(Shader &shader) override;
    void applyTransformVertices();
    void snapToWholeVerts();

    std::stringstream writeToString();
};


#endif //PROJECTBAHAMUT_BRUSH_H
