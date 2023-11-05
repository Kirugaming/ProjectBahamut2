//
// Created by kirut on 11/4/2023.
//

#include <fstream>
#include "Script.h"

Script::Script(const std::string& scriptPath) {
    lua.open_libraries(sol::lib::base);

    try {
        lua.script_file(scriptPath);
    } catch (std::exception &exception) {
        std::cout << "SCRIPT FILE FAILED TO LOAD! \n" << exception.what() << std::endl;
    }
    std::cout << "And this is C++!" << std::endl;
}
