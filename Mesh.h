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
#include "Texture.h"



struct Vertex {
    glm::vec3 position;
    glm::vec3 normals;
    glm::vec2 texCoords;
};

struct Color {
    glm::vec3 diffuse;
//    glm::vec3 ambient;
//    glm::vec3 emissive;
//    glm::vec3 specular;
};

struct MeshTexture {
    Texture *texture;
    std::string type;
};

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<MeshTexture> textures;
    Color colors;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures, Color colors);
    virtual void draw(Shader &shader);
private:
    unsigned int VAO{}, VBO{}, EBO{};

    void setupMesh();
};


#endif //PROJECTBAHAMUT_MESH_H
