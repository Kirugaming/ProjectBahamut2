//
// Created by kirut on 12/18/2023.
//

#include "Brush.h"
#include "glad/glad.h"


Brush::Brush() : Mesh(cube.vertices, cube.indices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}) {
}

Brush::Brush(std::vector<Vertex> &inVertices, std::vector<unsigned int> &inIndices, Transform &inTransform) : Mesh(inVertices, inIndices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}), transform(inTransform) {

}

void Brush::draw(Shader &shader) {
    shader.editShaderWithMat4("model", transform.toMat4());
    Mesh::draw(shader);
}

Brush::Brush(int id, Transform transform1) : id(id), Mesh(cube.vertices, cube.indices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}) {
    transform = *new Transform(transform1);

}

//void Brush::applyTransformVertices() {
//    glm::mat4 model = transform.toMat4();
//
//    for (int i = 0; i < vertices.size(); ++i) {
//        vertices[i].position = glm::vec3(model * glm::vec4(cube.vertices[i].position, 1.0f));
//    }
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glNamedBufferSubData(VBO, 0, static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex)), vertices.data());
//
//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//}

void Brush::snapToWholeVerts() {
    if (isSnapEnabled) {
        transform.position = glm::floor(transform.position);
        transform.scale = glm::floor(transform.scale);
    }
}


std::stringstream Brush::writeToString() {
    std::stringstream brushData;

    brushData << "brush " << this->id << "\n";

    for (auto &vertex : vertices) {
        brushData << "vertex " << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << " " << vertex.normals.x << " " << vertex.normals.y << " " << vertex.normals.z << " " << vertex.texCoords.x << " " << vertex.texCoords.y << "\n";
    }

    brushData << "indices ";
    for (auto &index : indices) {
        brushData << index << " ";
    }

    brushData << "\ntransform " << transform.position.x << " " << transform.position.y << " " << transform.position.z << " " <<
                                transform.rotation.x << " " << transform.rotation.y << " " << transform.rotation.z << " " <<
                                transform.scale.x << " " << transform.scale.y << " " << transform.scale.z << "\n";

    brushData << "end";


    return brushData;
}

