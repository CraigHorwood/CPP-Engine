#ifndef _SHADER_H
#define _SHADER_H

#include <string>
#include <map>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define ATTR_POSITION 0
#define ATTR_TEX_COORD 1
#define ATTR_NORMAL 2

class Shader
{
public:
    Shader(std::string, std::string);
    ~Shader();
    void use();
    void setUniformLocation(std::string);
    void setUniform1i(std::string, int);
    void setUniform1f(std::string, float);
    void setUniform2f(std::string, float, float);
    void setUniform3f(std::string, float, float, float);
    void setUniformMatrix4f(std::string, float*);
private:
    GLuint compileShader(std::string, GLenum);
    GLuint program;
    std::map<std::string, GLint> uniformLocations;
protected:
};

#endif