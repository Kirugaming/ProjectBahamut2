//
// Created by kirut on 10/18/2023.
//

#ifndef PROJECTBAHAMUT_MAP_H
#define PROJECTBAHAMUT_MAP_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "GameObject.h"
#include "Brush.h"

class Map {
public:
    std::string path;
    std::string mapVersion;

    std::vector<GameObject*> gameObjects;
    std::vector<Brush*> brushList;

    Map();
    Map(const std::string& levelFile);

    void save() const;


private:
    static GameObject* addGameObject(const YAML::Node& object);
    Brush* addBrush(std::ifstream &mapFile, std::string &fileLine);
};


#endif //PROJECTBAHAMUT_MAP_H
