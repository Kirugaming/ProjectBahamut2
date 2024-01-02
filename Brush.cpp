//
// Created by kirut on 12/18/2023.
//

#include "Brush.h"
#include "glad/glad.h"

Brush::Brush() : Mesh(cube.vertices, cube.indices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}) {
}

void Brush::draw(Shader &shader) {
    applyTransformVertices();
    Mesh::draw(shader);
}

Brush::Brush(std::string name, Transform transform1) : name(std::move(name)), Mesh(cube.vertices, cube.indices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}) {
    transform = *new Transform(transform1);

}

void Brush::applyTransformVertices() {
    glm::mat4 model = transform.toMat4();

    for (int i = 0; i < vertices.size(); ++i) {
        vertices[i].position = glm::vec3(model * glm::vec4(cube.vertices[i].position, 1.0f));
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glNamedBufferSubData(VBO, 0, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data());

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Brush::snapToWholeVerts() {
    if (isSnapEnabled) {
        transform.position = glm::floor(transform.position);
        transform.scale = glm::floor(transform.scale);
    }
}
