//
// Created by kirut on 11/4/2023.
//

#ifndef PROJECTBAHAMUT_SCRIPT_H
#define PROJECTBAHAMUT_SCRIPT_H

#include <string>
#include <sol/sol.hpp>
#include "GameObject.h"

class GameObject;

class Script {
public:
    std::string path;
    sol::state lua;

    Script(const std::string& scriptPath, GameObject *attachedObject);
};

#endif //PROJECTBAHAMUT_SCRIPT_H
