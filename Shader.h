//
// Created by kirut on 9/4/2023.
//

#ifndef PROJECTBAHAMUT_SHADER_H
#define PROJECTBAHAMUT_SHADER_H

#include "glad/glad.h"
#include "glm/detail/type_mat4x4.hpp"
#include "glm/fwd.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

class Shader {
public:
    unsigned int programId;

    Shader();
    Shader(const std::string &vertSource, const std::string &fragSource);

    void use() const;
    void unUse() const;

    void setInt(const std::string &name, int value) const;
    void editShaderWithMat4(const char *uniformName, glm::mat4 matrix) const;
    void editShaderWithVec3(const char *uniformName, glm::vec3 &colors) const;

private:
    static void getShaderProgramLinkInfoLog(unsigned int shaderProgramID);
    static void getShaderCompileInfoLog(unsigned int shaderID);

};


#endif //PROJECTBAHAMUT_SHADER_H
