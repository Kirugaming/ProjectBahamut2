//
// Created by kirut on 10/25/2023.
//

#include <string>

#ifndef PROJECTBAHAMUT_TEXTURE_H
#define PROJECTBAHAMUT_TEXTURE_H

#endif //PROJECTBAHAMUT_TEXTURE_H


class Texture {

public:
    explicit Texture(const std::string& filePath);

    unsigned int id;
    std::string path;
};