//
// Created by kirut on 12/18/2023.
//

#ifndef PROJECTBAHAMUT_BRUSH_H
#define PROJECTBAHAMUT_BRUSH_H

#include <vector>
#include "Shader.h"
#include "Mesh.h"
#include "yaml-cpp/node/node.h"
#include "../Types.h"

typedef struct Plane {
    // future: incorporate vertex struct containing vertex, normal, texcoord
    glm::vec3 normal;
    float distance;
    std::vector<glm::vec3> vertices;
} plane;

class Brush {
    unsigned int VAO{}, VBO{};
    void create(int numSides);
public:
    int id;
    std::vector<Plane> planes;
    std::vector<unsigned int> indices;
    size_t numVertices = 0;
    Transform transform;
    bool isSnapEnabled = true;

    Brush();
    Brush(std::vector<Vertex> &inVertices, std::vector<unsigned int> &inIndices, Transform &inTransform);
    Brush(int id, Transform transform1);

    void draw(Shader &shader);
    void applyTransformVertices();
    void snapToWholeVerts();
    bool checkRayIntersection(glm::vec3 rayCoords, glm::vec3 rayOrigin);

    std::stringstream writeToString();
};


#endif //PROJECTBAHAMUT_BRUSH_H
