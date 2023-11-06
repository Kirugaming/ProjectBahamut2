//
// Created by kirut on 11/4/2023.
//

#include <fstream>
#include "Script.h"

Script::Script(const std::string& scriptPath, GameObject *attachedObject) : path(scriptPath) {
    lua.open_libraries(sol::lib::base);

    // you need to make these available in lua
    lua.new_usertype<GameObject>("GameObject",
                                 "name", &GameObject::name,
                                 "transform", &GameObject::transform);
    lua.new_usertype<Transform>("Transform", // need by game object
                                "position", &Transform::position,
                                "rotation", &Transform::rotation,
                                "scale", &Transform::scale);
    lua.new_usertype<glm::vec3>("vec3", // need by transform
                                "x", &glm::vec3::x,
                                "y", &glm::vec3::y,
                                "z", &glm::vec3::z);


    lua["gameObject"] = attachedObject;

    try {
        lua.script_file(scriptPath);
    } catch (std::exception &exception) {
        std::cout << "SCRIPT FILE FAILED TO LOAD! \n" << exception.what() << std::endl;
    }
}