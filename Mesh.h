//
// Created by kirut on 9/29/2023.
//

#ifndef PROJECTBAHAMUT_MESH_H
#define PROJECTBAHAMUT_MESH_H

#include <string>
#include <vector>
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include "Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normals;
    glm::vec2 texCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader &shader);
private:
    unsigned int VAO{}, VBO{}, EBO{};

    void setupMesh();
};


#endif //PROJECTBAHAMUT_MESH_H