//
// Created by kirut on 12/18/2023.
//

#include "Brush.h"
#include "glad/glad.h"

Brush::Brush() : Mesh(cube.vertices, cube.indices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}) {

}

void Brush::draw(Shader &shader) {
    shader.editShaderWithMat4("model", transform.toMat4());
    Mesh::draw(shader);
}
