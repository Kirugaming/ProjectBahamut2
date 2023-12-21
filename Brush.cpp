//
// Created by kirut on 12/18/2023.
//

#include "Brush.h"
#include "glad/glad.h"

Brush::Brush(BrushShapes shape) {
    vertices = { // cube vertices
            -0.5f, -0.5f, -0.5f,    1.0f, 1.0f,

            0.5f, -0.5f, -0.5f,    1.0f, 1.0f,

            0.5f, 0.5f, -0.5f,    1.0f, 1.0f,

            -0.5f, 0.5f, -0.5f,    1.0f, 1.0f,

            -0.5f, -0.5f, 0.5f,    1.0f, 1.0f,

            0.5f, -0.5f, 0.5f,    1.0f, 1.0f,

            0.5f, 0.5f, 0.5f,    1.0f, 1.0f,

            -0.5f, 0.5f, 0.5f,    1.0f, 1.0f
    };

    indices = {
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

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // vertices to buffer
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    // vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);

}

void Brush::draw(glm::mat4 cameraView) const {
    shader.use();
    this->shader.editShaderWithMat4("view", cameraView);
    this->shader.editShaderWithMat4("perspective", glm::perspective(glm::radians(45.0f), (float)640 / (float)480, 0.1f, 100.0f));
    this->shader.editShaderWithMat4("model", transform.toMat4());

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

    shader.unUse();
}
