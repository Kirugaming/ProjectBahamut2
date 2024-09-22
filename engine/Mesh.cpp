//
// Created by kirut on 9/29/2023.
//

#include "Mesh.h"

#include <utility>

Mesh::Mesh() {
    // Cube
    vertices = {
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 0: bottom-left-back
            {{0.5f, -0.5f, -0.5f},  {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 1: bottom-right-back
            {{0.5f,  0.5f, -0.5f},  {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // 2: top-right-back
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // 3: top-left-back
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // 4: bottom-left-front
            {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // 5: bottom-right-front
            {{0.5f,  0.5f,  0.5f},  {0.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // 6: top-right-front
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}  // 7: top-left-front
    };

    indices = {
            0, 1, 2, 2, 3, 0, // back face
            4, 5, 6, 6, 7, 4, // front face
            0, 1, 5, 5, 4, 0, // bottom face
            2, 3, 7, 7, 6, 2, // top face
            0, 3, 7, 7, 4, 0, // left face
            1, 2, 6, 6, 5, 1  // right face
    };

    // VAO, VBO, EBO Setup
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), indices.data(), GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<MeshTexture> textures, Color colors) {
    this->vertices = std::move(vertices);
    this->indices = std::move(indices);
    this->textures = std::move(textures);
    this->colors = colors;

    setupMesh();
}



void Mesh::draw(Shader &shader) {
    unsigned int dcount = 1;
    unsigned int scount = 1;
    for (unsigned int i = 0; i < textures.size(); i++) {
        std::string number;
        std::string name = textures[i].type;
        if(name == "texture_diffuse")
            number = std::to_string(dcount++);
        else if(name == "texture_specular")
            number = std::to_string(scount++);

        shader.setInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].texture->id);
        glActiveTexture(GL_TEXTURE0+i);
    }

    // colors
    // Currently Models must have textures to use colors
    glm::vec3 finalColor = colors.diffuse; // we only need diffuse for now
//    shader.editShaderWithVec3("colors", finalColor);
    shader.editShaderWithVec3("colors", glm::vec3(1.0f, 1.0f, 1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    size_t vertexInBytes = vertices.size() * sizeof(Vertex);

    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertexInBytes), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(indices.size() * sizeof(unsigned int)), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)nullptr);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    glBindVertexArray(0);
}

// https://en.wikipedia.org/wiki/Slab_method
bool Mesh::isAABBIntersect(glm::vec3 rayOrigin, glm::vec3 rayDir) {
    // Get Bounds
    glm::vec3 minBounds = vertices[0].position;
    glm::vec3 maxBounds = vertices[0].position;

    for (int i = 1; i < vertices.size(); i++) {
        minBounds.x = std::min(minBounds.x, vertices[i].position.x);
        minBounds.y = std::min(minBounds.y, vertices[i].position.y);
        minBounds.z = std::min(minBounds.z, vertices[i].position.z);

        maxBounds.x = std::max(maxBounds.x, vertices[i].position.x);
        maxBounds.y = std::max(maxBounds.y, vertices[i].position.y);
        maxBounds.z = std::max(maxBounds.z, vertices[i].position.z);
    }

    glm::vec3 tLow(0.0f);
    glm::vec3 tHigh(0.0f);
    for (int i = 0; i < 3; ++i) {
        tLow[i] = (minBounds[i] - rayOrigin[i]) / rayDir[i];
        tHigh[i] = (maxBounds[i] - rayOrigin[i]) / rayDir[i];
    }

    glm::vec3 tiClose(0.0f);
    glm::vec3 tiFar(0.0f);
    for (int i = 0; i < 3; ++i) {
        tiClose[i] = std::min(tLow[i], tHigh[i]);
        tiFar[i] = std::max(tLow[i], tHigh[i]);
    }

    float tClose = std::numeric_limits<float>::min();
    float tFar = std::numeric_limits<float>::max();
    for (int i = 0; i < 3; ++i) {
        tClose = std::max(tiClose[i], tClose);
        tFar = std::min(tiFar[i], tFar);
    }

    if (tClose <= tFar) {
        return true;
    }
    return false;
}
