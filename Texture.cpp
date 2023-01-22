#include "Texture.h"
#include <string>
#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "lodepng.h"

using namespace std;

void Texture::init(string path)
{
    init(path, false);
}

void Texture::init(string path, bool skybox)
{
    this->skybox = skybox;
    valid = false;
    vector<unsigned char> image;
    unsigned error = lodepng::decode(image, w, h, path);
    if (error)
    {
        cout << "Failed to load texture: " << lodepng_error_text(error) << endl;
        return;
    }

    valid = true;
    if (skybox)
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        for (unsigned int i = 0; i < 6; i++)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
            if (i < 5)
            {
                path[path.length() - 5]++;
                lodepng::decode(image, w, h, path);
            }
        }
    }
    else
    {
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
    }
}

Texture::~Texture()
{
    if (valid) glDeleteTextures(1, &texture);
}

void Texture::bind()
{
    glBindTexture(skybox ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D, texture);
}