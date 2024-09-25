//
// Created by kirut on 12/18/2023.
//

#include "Brush.h"
#include "glad/glad.h"


Brush::Brush() {
//    create(4);
//
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//
//    glBindVertexArray(VAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    for (const auto& plane : planes) {
//        numVertices += plane.vertices.size();
//    }
//
//    std::vector<glm::vec3> flattenedVerts;
//    flattenedVerts.reserve(numVertices);
//    for (const auto& plane : planes) {
//        flattenedVerts.insert(flattenedVerts.end(), plane.vertices.begin(), plane.vertices.end());
//    }
//
//    // Upload vertices data to the VBO
//    glBufferData(GL_ARRAY_BUFFER, flattenedVerts.size() * sizeof(glm::vec3), flattenedVerts.data(), GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)nullptr);
//
//
//    glBindVertexArray(0);
}

//Brush::Brush(std::vector<Vertex> &inVertices, std::vector<unsigned int> &inIndices, Transform &inTransform) : Mesh(inVertices, inIndices, {}, {glm::vec3(1.0f, 1.0f, 1.0f)}), transform(inTransform) {
//
//}

void Brush::draw(Shader &shader) {
    shader.setMat4("model", transform.toMat4());

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

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

bool Brush::checkRayIntersection(glm::vec3 rayCoords, glm::vec3 rayOrigin) {

    return false;
}

void Brush::create(int numSides) {
//    // num has to be greater than 2
//    // create rest of sides from angle from num of sides
//    if (numSides >= 3) {
//        float angle = glm::radians(360.0f / numSides);
//        Plane top;
//        Plane bottom;
//        glm::mat4 unAngle = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//        for (int i = 0; i < numSides; ++i) {
//            Plane side;
//            float angle1 = i * angle;
//            float angle2 = (i + 1) * angle;
//
//            // top slice
//            top.vertices.emplace_back(0.0f, 1.0f / 2.0f, 0.0f); // middle
//            top.vertices.emplace_back(std::sin(angle1)/2, 1.0f / 2.0f, std::cos(angle1)/2); // left
//            top.vertices.emplace_back(std::sin(angle2)/2, 1.0f / 2.0f, std::cos(angle2)/2); // right
//            // side
//            // left tri
//            side.vertices.emplace_back(std::sin(angle1)/2, 1.0f / 2.0f, std::cos(angle1)/2);
//            side.vertices.emplace_back(std::sin(angle2)/2, 1.0f / 2.0f, std::cos(angle2)/2);
//            side.vertices.emplace_back(std::sin(angle1)/2, -1.0f / 2.0f, std::cos(angle1)/2);
//            // right tri
//            side.vertices.emplace_back(std::sin(angle1)/2, -1.0f / 2.0f, std::cos(angle1)/2);
//            side.vertices.emplace_back(std::sin(angle2)/2, -1.0f / 2.0f, std::cos(angle2)/2);
//            side.vertices.emplace_back(std::sin(angle2)/2, 1.0f / 2.0f, std::cos(angle2)/2);
//            // bottom slice
//            bottom.vertices.emplace_back(0.0f, -1.0f / 2.0f, 0.0f);
//            bottom.vertices.emplace_back(std::sin(angle1)/2, -1.0f / 2.0f, std::cos(angle1)/2);
//            bottom.vertices.emplace_back(std::sin(angle2)/2, -1.0f / 2.0f, std::cos(angle2)/2);
//
//            // the shape is angled so rotate it 45 degrees mainly so the face of a cube is facing the camera when created
//            for (auto & vertex : side.vertices) {
//                vertex = unAngle * glm::vec4(vertex, 1.0f);
//            }
//            planes.push_back(side);
//        }
//        for (auto & vertex : top.vertices) {
//            vertex = unAngle * glm::vec4(vertex, 1.0f);
//        }
//        for (auto & vertex : bottom.vertices) {
//            vertex = unAngle * glm::vec4(vertex, 1.0f);
//        }
//        planes.push_back(top);
//        planes.push_back(bottom);
//
//        // get normal and distance for each plane
//        for (plane& p : planes) {
//           glm::vec3 AB = p.vertices[1] - p.vertices[0];
//           glm::vec3 AC = p.vertices[2] - p.vertices[0];
//           p.normal = glm::normalize(glm::cross(AB, AC));
//
//           p.distance = glm::dot(p.normal, p.vertices[0]);
//        }
//    }
}


