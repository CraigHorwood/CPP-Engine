#include "Shader.h"
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

using namespace std;

void Shader::init(string vertexShaderPath, string fragmentShaderPath)
{
    ifstream vertexShaderStream(vertexShaderPath);
    if (!vertexShaderStream.is_open())
    {
        cout << "Could not open vertex shader at " << vertexShaderPath << endl;
        return;
    }
    string vertexShaderCode((istreambuf_iterator<char>(vertexShaderStream)), istreambuf_iterator<char>());
    ifstream fragmentShaderStream(fragmentShaderPath);
    if (!fragmentShaderStream.is_open())
    {
        cout << "Could not open fragment shader at" << fragmentShaderPath << endl;
        return;
    }
    string fragmentShaderCode((istreambuf_iterator<char>(fragmentShaderStream)), istreambuf_iterator<char>());
    GLuint vertexShader = compileShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glBindAttribLocation(program, ATTR_POSITION, "position");
    glBindAttribLocation(program, ATTR_TEX_COORD, "texCoords");
    glBindAttribLocation(program, ATTR_NORMAL, "normal");
    glLinkProgram(program);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::use()
{
    glUseProgram(program);
}

void Shader::setUniformLocation(string name)
{
    uniformLocations.insert(make_pair(name, glGetUniformLocation(program, name.c_str())));
}

void Shader::setUniform1i(string name, int i)
{
    glUniform1i(uniformLocations[name], i);
}

void Shader::setUniform1f(string name, float f)
{
    glUniform1f(uniformLocations[name], f);
}

void Shader::setUniform2f(string name, float x, float y)
{
    glUniform2f(uniformLocations[name], x, y);
}

void Shader::setUniform3f(string name, float x, float y, float z)
{
    glUniform3f(uniformLocations[name], x, y, z);
}

void Shader::setUniformMatrix4f(string name, float* matrix)
{
    glUniformMatrix4fv(uniformLocations[name], 1, false, matrix);
}

GLuint Shader::compileShader(string sourceStr, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char* source = sourceStr.c_str();
    GLint sourceSize = (GLint) sourceStr.size();
    glShaderSource(shader, 1, &source, &sourceSize);
    glCompileShader(shader);
    return shader;
}