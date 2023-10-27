//
// Created by kirut on 10/18/2023.
//

#ifndef PROJECTBAHAMUT_LEVEL_H
#define PROJECTBAHAMUT_LEVEL_H

#include <string>
#include <yaml-cpp/yaml.h>
#include "GameObject.h"

class Level {
public:
    std::string path;
    std::vector<GameObject*> gameObjects;

    Level();
    Level(const std::string& levelFile);

    void save() const;


private:
};


#endif //PROJECTBAHAMUT_LEVEL_H
