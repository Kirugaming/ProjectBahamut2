//
// Created by kirut on 10/18/2023.
//

#include "Level.h"

Level::Level() = default;

Level::Level(const std::string& levelFile) {
    path = levelFile;
    try {
        YAML::Node level = YAML::LoadFile(levelFile);
        
        // go through game objects
        for (auto &&object : level["GameObjects"]) {
            auto *newGameObject = new GameObject(
                    object["name"].as<std::string>(),
                    object["model"].as<std::string>(),
                    glm::vec3(object["position"][0].as<float>(), object["position"][1].as<float>(), object["position"][2].as<float>()),
                    glm::vec3(object["rotation"][0].as<float>(), object["rotation"][1].as<float>(), object["rotation"][2].as<float>()),
                    glm::vec3(object["scale"][0].as<float>(), object["scale"][1].as<float>(), object["scale"][2].as<float>())
            );
            // script needs info from attached game object
            newGameObject->script = new Script(object["script"].as<std::string>(), newGameObject);
            gameObjects.push_back(newGameObject);
        }
        for (int i = 0; i < level["GameObjects"].size(); ++i) {
            YAML::Node object = level["GameObjects"][i];

        }
    } catch (const std::exception& e) {
        std::cerr << "Map Loading Error: " << e.what() << std::endl;
    }
}

void Level::save() const {
    std::ofstream file(path);
    file << "# -ProjectBahamut Map File-\n# You can edit the map through this file or the engine\n";

    YAML::Node map;
    for (int i = 0; i < gameObjects.size(); i++) {
        map["GameObjects"][i]["name"] = gameObjects[i]->name;
        map["GameObjects"][i]["model"] = gameObjects[i]->model.modelPath;
        // position
        map["GameObjects"][i]["position"][0] = gameObjects[i]->transform.position.x;
        map["GameObjects"][i]["position"][1] = gameObjects[i]->transform.position.y;
        map["GameObjects"][i]["position"][2] = gameObjects[i]->transform.position.z;
        // rotation
        glm::vec3 vecRotation = glm::eulerAngles(gameObjects[i]->transform.rotation);
        map["GameObjects"][i]["rotation"][0] = vecRotation.x;
        map["GameObjects"][i]["rotation"][1] = vecRotation.y;
        map["GameObjects"][i]["rotation"][2] = vecRotation.z;
        // scale
        map["GameObjects"][i]["scale"][0] = gameObjects[i]->transform.scale.x;
        map["GameObjects"][i]["scale"][1] = gameObjects[i]->transform.scale.y;
        map["GameObjects"][i]["scale"][2] = gameObjects[i]->transform.scale.z;
        // any scripts
        map["GameObjects"][i]["script"] = gameObjects[i]->script->path;
    }

    file << map;
    file.close();

}
