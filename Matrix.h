#ifndef _MATRIX_H
#define _MATRIX_H

void loadIdentityMatrix(float*);
void loadOrthographicProjectionMatrix(float*, float, float, float, float, float, float);
void loadPerspectiveProjectionMatrix(float*, float, float, float, float);
void multiplyMatrix(float*, float*);
void translateMatrix(float*, float, float, float);
void rotateXMatrix(float*, float);
void rotateYMatrix(float*, float);
void rotateZMatrix(float*, float);

#endif