//
// Created by kirut on 10/25/2023.
//

#include <string>
#include "glad/glad.h"
#include "stb_image.h"
#include <iostream>

#ifndef PROJECTBAHAMUT_TEXTURE_H
#define PROJECTBAHAMUT_TEXTURE_H

#endif //PROJECTBAHAMUT_TEXTURE_H


class Texture {

public:
    unsigned int id;
    std::string path;

    explicit Texture(const char* filePath);


};