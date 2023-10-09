//
// Created by kirut on 9/4/2023.
//

#include "Shader.h"

Shader::Shader() : Shader("shaders/shader.vert", "shaders/shader.frag") {}

Shader::Shader(const std::string &vertSource, const std::string &fragSource) {
    std::string vertCode;
    std::string fragCode;
    std::ifstream vertFile;
    std::ifstream fragFile;
    // exception
    vertFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    // load glsl code from text file
    try {
        std::stringstream vertStream, fragStream;
        vertFile.open(vertSource);
        fragFile.open(fragSource);

        vertStream << vertFile.rdbuf();
        fragStream << fragFile.rdbuf();

        vertFile.close();
        fragFile.close();

        vertCode = vertStream.str();
        fragCode = fragStream.str();
    } catch (std::exception &exception) {
        std::cout << "SHADER CODE FAILED TO LOAD! \n" << exception.what() << std::endl;
    }

    const char* vCode = vertCode.c_str();
    const char* fCode = fragCode.c_str();

    // compile glsl code
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vCode, nullptr);
    glCompileShader(vertex);
    getShaderCompileInfoLog(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fCode, nullptr);
    glCompileShader(fragment);
    getShaderCompileInfoLog(fragment);

    // shader program
    programId = glCreateProgram();
    if (programId <= 0) {
        std::cout << "Shader program creation failed!" << std::endl;
        return;
    }
    glAttachShader(programId, vertex);
    glAttachShader(programId, fragment);
    glLinkProgram(programId);
    // program errors
    getShaderProgramLinkInfoLog(programId);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() const {
    glUseProgram(this->programId);
}
void Shader::unUse() const {
    glUseProgram(0);
}


void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->programId, name.c_str()), value);
}
void Shader::editShaderWithMat4(const char *uniformName, glm::mat4 matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(this->programId, uniformName), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::editShaderWithVec3(const char *uniformName, glm::vec3 &colors) const {
    glUniform3fv(glGetUniformLocation(this->programId,uniformName),1,glm::value_ptr(colors));
}

void Shader::getShaderProgramLinkInfoLog(unsigned int shaderProgramID) {
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cout << "Shader program failed to link! - \n" << infoLog << std::endl;
    }
}
void Shader::getShaderCompileInfoLog(unsigned int shaderID) {
    int success;
    char infoLog[512];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shaderID, 512, nullptr, infoLog);
        // get shaders type and print
        std::cout << "Shader failed to compile! - " << infoLog << std::endl;
    }
}

