//
// Created by kirut on 9/14/2024.
//

#ifndef PROJECTBAHAMUT_BASEDRAWABLE_H
#define PROJECTBAHAMUT_BASEDRAWABLE_H

#include "Shader.h"

class BaseDrawable {
public:
    virtual void draw(Shader &shader) = 0;
};


#endif //PROJECTBAHAMUT_BASEDRAWABLE_H
