//
// Created by kirut on 10/18/2023.
//

#include "Map.h"

Map::Map() = default;

Map::Map(const std::string& mapFilePath) {
    path = mapFilePath;
    std::ifstream mapFile(mapFilePath);
    if (mapFile.peek() != std::ifstream::traits_type::eof()) { // no need to add any map things if empty file
        try {
            std::string fileLine;

            while (std::getline(mapFile, fileLine)) { // get rid of top comments
                if (!fileLine.starts_with("# ")) {
                    mapVersion = fileLine;
                    break;
                }
            }


            while(std::getline(mapFile, fileLine)) {
                if (fileLine.starts_with("brush")) {
                    brushList.push_back(addBrush(mapFile, fileLine));
                } else if (fileLine.starts_with("gameobject")) {

                }
            }
        } catch (const std::exception& e) {
        std::cerr << "Map Loading Error: " << e.what() << std::endl;
        }
    }
}

void Map::save() const {
    std::ofstream file(path);
    file << "# -Battle Engine Map-\n"
            "# brush = brush start\n"
            "# vertex = position(x, y, z), normals(x, y, z), texCoords(x, y)\n"
            "# indices = vertex index, , , , vertex index\n"
            "# transform = position(x, y, z), rotation(x, y, z), scale(x, y, z)\n"
            "# end = end of serialization\n"
            "v0.2.5\n"; // .bem version for compatibility checks in the future

    for (auto i : brushList) {
        file << i->writeToString().rdbuf();
    }

    file.close();

}

Brush *Map::addBrush(std::ifstream &mapFile, std::string &fileLine) {
    std::vector<Vertex> newVertices;
    std::vector<unsigned int> newIndices;
    Transform newTransform;

    while (std::getline(mapFile, fileLine)) {
        std::istringstream iss(fileLine);

        std::string type;
        iss >> type;
        if (type == "vertex") {
            Vertex newVertex{};
            float x, y, z;
            // position
            iss >> x;
            iss >> y;
            iss >> z;
            newVertex.position = glm::vec3(x, y, z);
            // normals
            iss >> x;
            iss >> y;
            iss >> z;
            newVertex.normals = glm::vec3(x, y, z);
            // tex coords
            iss >> x;
            iss >> y;
            newVertex.texCoords = glm::vec2(x, y);

            newVertices.push_back(newVertex);
        } else if (type == "indices") {
            int index;

            while (iss >> index) {
                newIndices.push_back(index);
            }

        } else if (type == "transform") {
            float x, y, z;
            // position
            iss >> x;
            iss >> y;
            iss >> z;
            newTransform.position = glm::vec3(x, y, z);
            // rotation
            iss >> x;
            iss >> y;
            iss >> z;
            newTransform.rotation = glm::vec3(x, y, z);
            // scale
            iss >> x;
            iss >> y;
            iss >> z;
            newTransform.scale = glm::vec3(x, y, z);

        } else if (type == "end") {
            break;
        }
    }

    return new Brush(newVertices, newIndices, newTransform);
}

//GameObject* Map::addGameObject(const YAML::Node &object) {
//    auto *newGameObject = new GameObject(
//            object["name"].as<std::string>(),
//            object["model"].as<std::string>(),
//            glm::vec3(object["position"][0].as<float>(), object["position"][1].as<float>(), object["position"][2].as<float>()),
//            glm::vec3(object["rotation"][0].as<float>(), object["rotation"][1].as<float>(), object["rotation"][2].as<float>()),
//            glm::vec3(object["scale"][0].as<float>(), object["scale"][1].as<float>(), object["scale"][2].as<float>())
//    );
//
//    for (int i = 0; i < object["scripts"].size(); ++i) {
//        newGameObject->scripts.push_back(new Script(object["scripts"][i].as<std::string>(), newGameObject));
//    }
//
////    for (int i = 0; i < object["nestedObjects"].size(); ++i) {
////        newGameObject->nestedGameObjects.push_back(
////                addGameObject(object["nestedObjects"][i]));
////    }
//
//    return newGameObject;
//}
//
