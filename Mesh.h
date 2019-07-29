#ifndef _MESH_H
#define _MESH_H

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

typedef struct Triangle
{
    float x0, y0, z0;
    float x1, y1, z1;
    float x2, y2, z2;
    float xNormal, yNormal, zNormal;
    float d;
} Triangle;

class Mesh
{
public:
    Mesh(std::string);
    ~Mesh();
    void bind();
    void render(float, float, float);
    Triangle* triangles;
    unsigned int triangleCount;
private:
    bool valid;
    GLuint vbo, ibo;
protected:
};

#endif