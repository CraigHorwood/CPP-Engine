#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Texture
{
public:
    void init(std::string);
    void init(std::string, bool);
    ~Texture();
    void bind();
private:
    bool skybox, valid;
    unsigned int w, h;
    GLuint texture;
protected:
};

#endif