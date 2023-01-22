#ifndef _MODEL_H
#define _MODEL_H

#include <string>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

typedef struct ModelPart {
    Mesh* geometry;
    Texture* texture;
    Shader* shader;
} ModelPart;

class Model
{
public:
    void init(std::string);
    ~Model();
    void render(float, float, float);
private:
    bool valid;
    ModelPart* modelParts;
    unsigned int modelPartCount;
protected:
};

#endif