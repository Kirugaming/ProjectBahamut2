//
// Created by kirut on 11/4/2023.
//

#ifndef PROJECTBAHAMUT_SCRIPT_H
#define PROJECTBAHAMUT_SCRIPT_H

#include <string>
#include <sol/sol.hpp>

class Script {
public:
    sol::state lua;

    explicit Script(const std::string& scriptPath);
};

#endif //PROJECTBAHAMUT_SCRIPT_H
