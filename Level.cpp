//
// Created by kirut on 10/18/2023.
//

#include "Level.h"

Level::Level(const std::string& levelFile) {
    try {
        YAML::Node level = YAML::LoadFile(levelFile);
        
        // go through game objects
        for (int i = 0; i < level["GameObjects"].size(); ++i) {
            gameObjects.push_back(
                    new GameObject(
                            level["GameObjects"][i]["name"].as<std::string>(),
                        level["GameObjects"][i]["model"].as<std::string>())
                    );
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

Level::Level() = default;
