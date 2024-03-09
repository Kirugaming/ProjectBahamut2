//
// Created by kirut on 12/18/2023.
//

#include "Brush.h"
#include "glad/glad.h"


Brush::Brush() {
    create(4);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    for (const auto& plane : planes) {
        numVertices += plane.vertices.size();
    }

    std::vector<glm::vec3> flattenedVerts;
    flattenedVerts.reserve(numVertices);
    for (const auto& plane : planes) {
        flattenedVerts.insert(flattenedVerts.end(), plane.vertices.begin(), plane.vertices.end());
    }

    // Upload vertices data to the VBO
    glBufferData(GL_ARRAY_BUFFER, flattenedVerts.size() * sizeof(glm::vec3), flattenedVerts.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);


    glBindVertexArray(0);
}

//Brush::Brush(std::vector<Vertex> &inVertices, std::vector<unsigned int> &inIndices, Transform &inTransform) : Mesh(inVertices, inIndices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}), transform(inTransform) {
//
//}

void Brush::draw(Shader &shader) {
    shader.editShaderWithMat4("model", transform.toMat4());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

//Brush::Brush(int id, Transform transform1) : id(id), Mesh(cube.vertices, cube.indices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}) {
//    transform = *new Transform(transform1);
//}

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

    brushData << "brush\n";

//    for (auto &vertex : vertices) {
//        brushData << "vertex " << vertex.position.x << " " << vertex.position.y << " " << vertex.position.z << " "
//                            << vertex.normals.x << " " << vertex.normals.y << " " << vertex.normals.z << " "
//                            << vertex.texCoords.x << " " << vertex.texCoords.y << "\n";
//    }
//
//    brushData << "indices ";
//    for (auto &index : indices) {
//        brushData << index << " ";
//    }
//
//    brushData << "\ntransform " << transform.position.x << " " << transform.position.y << " " << transform.position.z << " " <<
//                                transform.rotation.x << " " << transform.rotation.y << " " << transform.rotation.z << " " <<
//                                transform.scale.x << " " << transform.scale.y << " " << transform.scale.z << "\n";

    brushData << "end";


    return brushData;
}

bool Brush::checkRayIntersection(glm::vec3 rayCoords) {

    return false;
}

void Brush::create(int numSides) {
    // num has to be greater than 2
    // TODO: DISTANCE, NORMALS
    plane firstPlane;
    firstPlane.vertices.emplace_back(-0.5f, -0.5f, -0.5f);
    firstPlane.vertices.emplace_back(0.5f, -0.5f, -0.5f);
    firstPlane.vertices.emplace_back(0.5f,  0.5f, -0.5f);
    firstPlane.vertices.emplace_back(-0.5f, -0.5f, -0.5f);
    firstPlane.vertices.emplace_back(-0.5f, 0.5f, -0.5f);
    firstPlane.vertices.emplace_back(0.5f, 0.5f, -0.5f);
    planes.push_back(firstPlane);

    // create rest of sides from angle from num of sides
    if (numSides >= 3) {
        float angle = glm::radians(360.0f / numSides);
        for (int i = 1; i < numSides; ++i) {
            plane p;
            plane lastPlane = planes.back();
            glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
            p.vertices.emplace_back(rotMat * glm::vec4(lastPlane.vertices[0], 1.0f));
            p.vertices.emplace_back(rotMat * glm::vec4(lastPlane.vertices[1], 1.0f));
            p.vertices.emplace_back(rotMat * glm::vec4(lastPlane.vertices[2], 1.0f));
            p.vertices.emplace_back(rotMat * glm::vec4(lastPlane.vertices[3], 1.0f));
            p.vertices.emplace_back(rotMat * glm::vec4(lastPlane.vertices[4], 1.0f));
            p.vertices.emplace_back(rotMat * glm::vec4(lastPlane.vertices[5], 1.0f));
            planes.push_back(p);
        }
    }
    plane bottomPlane;
    plane topPlane;
    // complete top and bottom
    for (auto & plane : planes) {


        bottomPlane.vertices.emplace_back(plane.vertices[0]);
        bottomPlane.vertices.emplace_back(0.0f, -0.5f, 0.0f); // you could get the y position for the bottom verts but i hard coded
        bottomPlane.vertices.emplace_back(plane.vertices[1]);

        topPlane.vertices.emplace_back(plane.vertices[4]);
        topPlane.vertices.emplace_back(0.0f, 0.5f, 0.0f);
        topPlane.vertices.emplace_back(plane.vertices[5]);


    }
    planes.push_back(bottomPlane);
    planes.push_back(topPlane);
}

