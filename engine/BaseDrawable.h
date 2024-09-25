//
// Created by kirut on 9/14/2024.
//

#ifndef PROJECTBAHAMUT_BASEDRAWABLE_H
#define PROJECTBAHAMUT_BASEDRAWABLE_H

#include "Shader.h"

/*
 * This Class allows drawable objects like lines and meshes to be stored in a list, so you can call each of their draws together
 */
class BaseDrawable {
public:
    virtual void draw(Shader &shader) = 0;
};


#endif //PROJECTBAHAMUT_BASEDRAWABLE_H
