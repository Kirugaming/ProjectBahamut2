//
// Created by kirut on 10/18/2023.
//

#ifndef PROJECTBAHAMUT_LEVEL_H
#define PROJECTBAHAMUT_LEVEL_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "GameObject.h"
#include "Brush.h"

class Level {
public:
    std::string path;
    std::vector<GameObject*> gameObjects;
    std::vector<Brush*> brushList;

    Level();
    Level(const std::string& levelFile);

    void save() const;


private:
    static GameObject* addGameObject(const YAML::Node& object);
};


#endif //PROJECTBAHAMUT_LEVEL_H
