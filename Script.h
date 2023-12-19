//
// Created by kirut on 11/4/2023.
//

#ifndef PROJECTBAHAMUT_SCRIPT_H
#define PROJECTBAHAMUT_SCRIPT_H

#include <string>
#include <sol/sol.hpp>
#include <filesystem>
#include "GameObject.h"

class GameObject;

class Script {
public:
    std::filesystem::path path;
    std::string scriptCode;
    sol::state lua;

    Script(const std::string&, GameObject *attachedObject);

    void run();
};

#endif //PROJECTBAHAMUT_SCRIPT_H
