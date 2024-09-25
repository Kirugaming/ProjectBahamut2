//
// Created by kirut on 9/14/2024.
//

#ifndef PROJECTBAHAMUT_LINE_H
#define PROJECTBAHAMUT_LINE_H


#include "BaseDrawable.h"
#include "glm/vec3.hpp"
#include "Shader.h"

class Line : public BaseDrawable {
    unsigned int VAO{}, VBO{};
    std::vector<glm::vec3> vertices;
    glm::vec3 color;

public:
    Line(glm::vec3 start, glm::vec3 end, glm::vec3 color);
    Line(std::vector<glm::vec3> vertices, glm::vec3 color);

    void draw(Shader &shader) override;
};


#endif //PROJECTBAHAMUT_LINE_H
