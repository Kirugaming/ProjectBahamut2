//
// Created by kirut on 10/18/2023.
//

#include "Level.h"

Level::Level() = default;

Level::Level(const std::string &projectPath, const std::string& levelFile) {
    try {
        YAML::Node level = YAML::LoadFile(levelFile);
        
        // go through game objects
        for (auto &&object : level["GameObjects"]) {
            gameObjects.push_back(
                    new GameObject(
                            object["name"].as<std::string>(),
                            projectPath + "/" + object["model"].as<std::string>(),
                            glm::vec3(object["position"][0].as<float>(), object["position"][1].as<float>(), object["position"][2].as<float>()),
                            glm::vec3(object["rotation"][0].as<float>(), object["rotation"][1].as<float>(), object["rotation"][2].as<float>()),
                            glm::vec3(object["scale"][0].as<float>(), object["scale"][1].as<float>(), object["scale"][2].as<float>())
                    )
            );
        }
        for (int i = 0; i < level["GameObjects"].size(); ++i) {
            YAML::Node object = level["GameObjects"][i];

        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
