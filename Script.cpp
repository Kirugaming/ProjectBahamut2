//
// Created by kirut on 11/4/2023.
//

#include <fstream>
#include "Script.h"
#include "InputManager.h"

Script::Script(const std::string& scriptPath, GameObject *attachedObject) : path(scriptPath) {

    lua.open_libraries(sol::lib::base);

    // you need to make these available in lua
    lua.new_usertype<GameObject>("GameObject",
                                 "name", &GameObject::name,
                                 "transform", &GameObject::transform);
    lua.new_usertype<Transform>("transform", // need by game object
                                "position", &Transform::position,
                                "rotation", &Transform::rotation,
                                "scale", &Transform::scale);
    lua.new_usertype<glm::vec3>("vec3", // need by transform
                                "x", &glm::vec3::x,
                                "y", &glm::vec3::y,
                                "z", &glm::vec3::z);

    lua.new_usertype<InputManager>("InputManager",
                                   "getKeyDown", &InputManager::getKeyDown);

    lua["InputManager"] = InputManager::getInstance();
    lua["gameObject"] = attachedObject;

    try {
        std::stringstream scriptStream;
        std::ifstream scriptFile;

        scriptFile.open(path.string());
        scriptStream << scriptFile.rdbuf();

        scriptFile.close();

        scriptCode = scriptStream.str();
    } catch (std::exception &exception) {
        std::cout << "SCRIPT FILE FAILED TO LOAD! \n" << exception.what() << std::endl;
    }
}

void Script::run() {
    lua.script(scriptCode);
}
