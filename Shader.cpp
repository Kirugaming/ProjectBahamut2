//
// Created by kirut on 9/4/2023.
//

#include "Shader.h"

Shader::Shader() : Shader("Assets/shaders/shader.vert", "Assets/shaders/shader.frag") {}

Shader::Shader(const std::string &vertSource, const std::string &fragSource) {
    const char* vertCode;
    const char* fragCode;
    std::ifstream vertFile;
    std::ifstream fragFile;
    // exception
    vertFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    // load glsl code from text file
    try {
        std::stringstream vertStream, fragStream;
        // vertex
        vertFile.open(vertSource);
        vertStream << vertFile.rdbuf();
        vertFile.close();
        vertCode = vertStream.str().c_str();
        // fragment
        fragFile.open(fragSource);
        fragStream << fragFile.rdbuf();
        fragFile.close();
        fragCode = fragStream.str().c_str();
    } catch (std::exception &exception) {
        std::cout << "SHADER CODE FAILED TO LOAD! \n" << exception.what() << std::endl;
    }

    // compile glsl code
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertCode, nullptr);
    glCompileShader(vertex);
    getShaderCompileInfoLog(vertex);

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragCode, nullptr);
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

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->programId, name.c_str()), value);
}
void Shader::editShaderWithMat4(const char *uniformName, glm::mat4 &matrix) const {
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
        std::cout << "Shader program failed to link! - " << infoLog << std::endl;
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
