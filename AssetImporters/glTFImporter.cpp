//
// Created by kirut on 9/24/2024.
//

#include <iostream>
#include "glTFImporter.h"
#include "../engine/Mesh.h"

import Utils;

glTF::Importer::Importer(std::ifstream &fileStream, glTF::gltfType type) {
    switch (type) {
        case Json:
            jsonInterpreter(fileStream);
            break;
        case Binary:
            std::cerr << "Binary for glTF not implemented!" << std::endl;
            throw std::exception();
            break;
    }
}

void glTF::Importer::jsonInterpreter(std::ifstream &fileStream) {
    json gltfJson = json::parse(fileStream);

    if (gltfJson["asset"]["version"] != "2.0") {
        std::cerr << "glTF Import Error: Incompatible glTF version!" << std::endl;
        throw std::exception();
    }


}

glTF::Scene glTF::Importer::parseScenes(const json& glTFJson) {
    unsigned int mainScene = glTFJson["scene"].get<unsigned int>();

    json sceneJson = glTFJson["scenes"][mainScene];

    Scene scene;
    if (sceneJson.contains("name"))
        scene.name = new std::string(sceneJson["name"].get<std::string>());

    if (sceneJson.contains("nodes")) {
        scene.nodes = new Node[sceneJson["nodes"].size()];
        for (int i = 0; i < sceneJson["nodes"].size(); ++i) {
            scene.nodes[i] = parseNodes(glTFJson, sceneJson["nodes"][i].get<unsigned int>());
        }
    }

    return scene;
}

glTF::Node glTF::Importer::parseNodes(const json &glTFJson, unsigned int index) {
    json nodeJson = glTFJson["nodes"][index];

    Node node;
    if (nodeJson.contains("name"))
        node.name = new std::string(nodeJson["name"].get<std::string>());
    if (nodeJson.contains("mesh")) {
        node.mesh = parseMesh(glTFJson, nodeJson["mesh"].get<unsigned int>());
    }

}

glTF::Mesh* glTF::Importer::parseMesh(const json &glTFJson, unsigned int index) {
    json meshJson = glTFJson["meshes"][index];

    Mesh mesh;
    if (meshJson.contains("name"))
        mesh.name = new std::string(meshJson["name"].get<std::string>());

    for (int i = 0; i < meshJson["primitives"].size(); ++i) {
        json primitiveJson = meshJson["primitives"][i];
        Mesh::Primitive primitive;

        if (primitiveJson["attributes"].contains("POSITION"))
            parseAccessor(glTFJson, primitiveJson["attributes"]["POSITION"].get<unsigned int>());


        mesh.primitives.push_back(primitive);
    }
}


glTF::Accessor glTF::Importer::parseAccessor(const json &glTFJson, unsigned int index) {
    json accessorJson = glTFJson["accessors"][index];
    Accessor accessor;

    if (accessorJson.contains("bufferView")) {
        accessor.bufferView = parseBufferView(glTFJson, accessorJson["bufferView"].get<unsigned int>());
    }

    return accessor;
}

glTF::BufferView* glTF::Importer::parseBufferView(const json &glTFJson, unsigned int index) {
    json bufferViewJson = glTFJson["bufferViews"][index];
    BufferView bufferView;


}

glTF::Buffer glTF::Importer::parseBuffer(const json &glTFJson, unsigned int index) {
    json bufferJson = glTFJson["buffers"][index];
    Buffer buffer;

    buffer.byteLength = bufferJson["byteLength"].get<unsigned int>();
    if (bufferJson.contains("uri")) {
        buffer.uri = new std::string(bufferJson["uri"].get<std::string>());
        buffer.parsedUri = base64Decode(*buffer.uri);
    }
    if (bufferJson.contains("name")) {
        buffer.name = new std::string(bufferJson["name"].get<std::string>());
    }

    return buffer;
}

std::vector<uint8_t> glTF::Importer::parseUri(const std::string& uri) {
    // if string
    std::string header = "data:application/octet-stream;base64,";
    return base64Decode(uri.substr(header.size()));
    // if file
}
