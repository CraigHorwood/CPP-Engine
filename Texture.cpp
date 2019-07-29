#include "Texture.h"
#include <string>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "BinaryStream.h"

using namespace std;

Texture::Texture(string path) : Texture(path, false)
{
}

Texture::Texture(string path, bool skybox)
{
    this->skybox = skybox;
    valid = false;
    BinaryStream stream(path);
    if (!stream.open)
    {
        cout << "Could not open texture at " << path << endl;
        return;
    }
    unsigned int header;
    stream.readUnsignedInt(&header);
    if (header != 0x54455830)
    {
        cout << "Invalid texture format at " << path << endl;
        return;
    }
    valid = true;
    stream.readUnsignedInt(&w);
    stream.readUnsignedInt(&h);
    char* pixels;
    size_t size = (w * h) << 2;
    pixels = new char[size];
    if (skybox)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        for (unsigned int i = 0; i < 6; i++)
        {
            stream.read(pixels, size);
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        }
        stream.close();
    }
    else
    {
        stream.read(pixels, size);
        stream.close();
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    }
    delete[] pixels;
}

Texture::~Texture()
{
    if (valid) glDeleteTextures(1, &texture);
}

void Texture::bind()
{
    glBindTexture(skybox ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, texture);
}