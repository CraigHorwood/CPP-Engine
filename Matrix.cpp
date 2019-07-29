#include "Matrix.h"
#include <string.h>
#include <math.h>

void loadIdentityMatrix(float* matrix)
{
    for (int i = 0; i < 16; i++)
    {
        if (i % 5 == 0) matrix[i] = 1.0f;
        else matrix[i] = 0.0f;
    }
}

void loadOrthographicProjectionMatrix(float* matrix, float left, float right, float bottom, float top, float near, float far)
{
    loadIdentityMatrix(matrix);
    matrix[0] = 2.0f / (right - left);
    matrix[5] = 2.0f / (top - bottom);
    matrix[10] = -2.0f / (far - near);
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[14] = -(far + near) / (far - near);
}

void loadPerspectiveProjectionMatrix(float* matrix, float fov, float ar, float near, float far)
{
    loadIdentityMatrix(matrix);
    fov *= 0.0087266f;
    matrix[0] = 1.0f / (ar * tanf(fov));
    matrix[5] = 1.0f / tanf(fov);
    matrix[10] = -(far + near) / (far - near);
    matrix[11] = -1.0f;
    matrix[14] = -(2 * far * near) / (far - near);
    matrix[15] = 0.0f;
}

void multiplyMatrix(float* transformMatrix, float* matrix)
{
    float matrixO[16];
    memcpy(matrixO, matrix, sizeof(float) << 4);
    for (int x = 0; x < 4; x++)
    {
        int column = x << 2;
        for (int y = 0; y < 4; y++)
        {
            float result = 0.0f;
            for (int i = 0; i < 4; i++)
            {
                result += transformMatrix[y + (i << 2)] * matrixO[i + column];
            }
            matrix[y + column] = result;
        }
    }
}

void translateMatrix(float* matrix, float x, float y, float z)
{
    if (x != 0.0f || y != 0.0f || z != 0.0f)
    {
        float translationMatrix[16];
        loadIdentityMatrix(translationMatrix);
        translationMatrix[12] = x;
        translationMatrix[13] = y;
        translationMatrix[14] = z;
        multiplyMatrix(translationMatrix, matrix);
    }
}

void rotateXMatrix(float* matrix, float angle)
{
    if (angle != 0.0f)
    {
        float rotationMatrix[16];
        loadIdentityMatrix(rotationMatrix);
        float rCos = cosf(angle);
        float rSin = sinf(angle);
        rotationMatrix[5] = rCos;
        rotationMatrix[6] = -rSin;
        rotationMatrix[9] = rSin;
        rotationMatrix[10] = rCos;
        multiplyMatrix(rotationMatrix, matrix);
    }
}

void rotateYMatrix(float* matrix, float angle)
{
    if (angle != 0.0f)
    {
        float rotationMatrix[16];
        loadIdentityMatrix(rotationMatrix);
        float rCos = cosf(angle);
        float rSin = sinf(angle);
        rotationMatrix[0] = rCos;
        rotationMatrix[2] = rSin;
        rotationMatrix[8] = -rSin;
        rotationMatrix[10] = rCos;
        multiplyMatrix(rotationMatrix, matrix);
    }
}

void rotateZMatrix(float* matrix, float angle)
{
    if (angle != 0.0f)
    {
        float rotationMatrix[16];
        loadIdentityMatrix(rotationMatrix);
        float rCos = cosf(angle);
        float rSin = sinf(angle);
        rotationMatrix[0] = rCos;
        rotationMatrix[1] = -rSin;
        rotationMatrix[4] = rSin;
        rotationMatrix[5] = rCos;
        multiplyMatrix(rotationMatrix, matrix);
    }
}