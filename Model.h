#ifndef _MODEL_H
#define _MODEL_H

#include <string>
#include "Mesh.h"

class Model
{
public:
    Model(std::string);
    ~Model();
    void render(float, float, float);
private:
    Mesh* materials;
protected:
};

#endif