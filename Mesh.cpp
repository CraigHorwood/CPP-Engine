#include "Mesh.h"
#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "BinaryStream.h"
#include <math.h>
#include <iostream>

using namespace std;

Mesh::Mesh(string path)
{
    valid = false;
    BinaryStream stream(path);
    if (!stream.open)
    {
        cout << "Could not open model at " << path << endl;
        return;
    }
    unsigned int header;
    stream.readUnsignedInt(&header);
    if (header != 0x4d444c30)
    {
        cout << "Invalid model format at " << path << endl;
        return;
    }
    valid = true;

    unsigned int vertexCount;
    stream.readUnsignedInt(&vertexCount);
    float* vertices;
    vertices = new float[vertexCount];
    for (unsigned int i = 0; i < vertexCount; i++)
    {
        stream.readFloat(&vertices[i]);
    }
    stream.readUnsignedInt(&triangleCount);
    unsigned short* indices;
    indices = new unsigned short[triangleCount];
    for (unsigned int i = 0; i < triangleCount; i++)
    {
        stream.readUnsignedShort(&indices[i]);
    }
    stream.close();

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleCount * sizeof(unsigned short), indices, GL_STATIC_DRAW);\
    triangles = new Triangle[triangleCount / 3];
    for (unsigned int i = 0; i < triangleCount; i += 3)
    {
        unsigned int i0 = indices[i] << 3;
        unsigned int i1 = indices[i + 1] << 3;
        unsigned int i2 = indices[i + 2] << 3;
        Triangle& t = triangles[i / 3];
        t.x0 = vertices[i0];
        t.y0 = vertices[i0 + 1];
        t.z0 = vertices[i0 + 2];
        t.x1 = vertices[i1];
        t.y1 = vertices[i1 + 1];
        t.z1 = vertices[i1 + 2];
        t.x2 = vertices[i2];
        t.y2 = vertices[i2 + 1];
        t.z2 = vertices[i2 + 2];
        t.xNormal = (t.y1 - t.y0) * (t.z2 - t.z1) - (t.z1 - t.z0) * (t.y2 - t.y1);
        t.yNormal = (t.z1 - t.z0) * (t.x2 - t.x1) - (t.x1 - t.x0) * (t.z2 - t.z1);
        t.zNormal = (t.x1 - t.x0) * (t.y2 - t.y1) - (t.y1 - t.y0) * (t.x2 - t.x1);
        float len = sqrtf(t.xNormal * t.xNormal + t.yNormal * t.yNormal + t.zNormal * t.zNormal);
        t.xNormal /= len;
        t.yNormal /= len;
        t.zNormal /= len;
        t.d = -t.xNormal * t.x0 - t.yNormal * t.y0 - t.zNormal * t.z0;
    }
    delete[] vertices;
    delete[] indices;
}

Mesh::~Mesh()
{
    if (valid)
    {
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ibo);
        delete[] triangles;
    }
}

void Mesh::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    const GLsizei stride = sizeof(float) << 3;
    glVertexAttribPointer(ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, stride, 0);
    glVertexAttribPointer(ATTR_TEX_COORD, 2, GL_FLOAT, GL_FALSE, stride, (void*) (sizeof(float) * 3));
    glVertexAttribPointer(ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, stride, (void*) (sizeof(float) * 5));
    glEnableVertexAttribArray(ATTR_POSITION);
    glEnableVertexAttribArray(ATTR_TEX_COORD);
    glEnableVertexAttribArray(ATTR_NORMAL);
}

// TODO: Model matrix to apply per-model translation and rotation.
void Mesh::render(float x, float y, float z)
{
    glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_SHORT, 0);
}