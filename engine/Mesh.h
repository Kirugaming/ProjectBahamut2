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
#include "../Texture.h"
#include "BaseDrawable.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Edge {
    glm::vec3 vertices[2];
    glm::vec3 position;

    Edge(glm::vec3 &vert1, glm::vec3 &vert2) : vertices(vert1, vert2) {
        position = (vert1 + vert2) / 2.0f;
    }
};

struct Face {
    glm::vec3 vertices[3];
    glm::vec3 position;
    
};

struct Color {
    glm::vec3 diffuse;
//    glm::vec3 ambient;
//    glm::vec3 emissive;
//    glm::vec3 specular;
};

struct MeshTexture { // to be changed later
    Texture *texture;
    std::string type;
};

class Mesh : private BaseDrawable {
    unsigned int VAO{}, VBO{}, EBO{};
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices; // defining the triangles

    void setupMesh();

public:
    enum InitialShape {
        Cube,
        Cylinder,
    };

    std::vector<MeshTexture> textures;
    Color colors = {{0, 0, 0}};

    /*
     * For creating simple convex hull shapes like cube and cylinder
     */
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures, Color colors);

    void draw(Shader &shader) override;
    bool isAABBIntersect(glm::vec3 rayOrigin, glm::vec3 rayDir);
};


#endif //PROJECTBAHAMUT_MESH_H
