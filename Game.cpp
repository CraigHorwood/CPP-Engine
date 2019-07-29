#include "Game.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Player.h"
#include "Matrix.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <vector>

using namespace std;

Game::Game()
{
    lightingShader = new Shader("assets/shaders/lighting.vsh", "assets/shaders/lighting.fsh");
    lightingShader->setUniformLocation("projectionMatrix");
    lightingShader->setUniformLocation("viewMatrix");
    skyShader = new Shader("assets/shaders/sky.vsh", "assets/shaders/sky.fsh");
    skyShader->setUniformLocation("projectionMatrix");
    skyShader->setUniformLocation("viewMatrix");
    skyTexture = new Texture("assets/textures/sky.tex", true);
    floorTexture = new Texture("assets/textures/floor.tex");
    grassTexture = new Texture("assets/textures/grass.tex");
    skyMesh = new Mesh("assets/models/sky.mdl");
    floorMesh = new Mesh("assets/models/floor.mdl");
    roomMesh = new Mesh("assets/models/room.mdl");
    loadPerspectiveProjectionMatrix(projectionMatrix, 70.0f, 16.0f / 9.0f, 0.0625f, 16.0f);
    loadIdentityMatrix(viewMatrix);
    player = new Player(this, 2.0f, 2.0f, -2.0f);
    keys[0] = false;
    keys[1] = false;
    keys[2] = false;
    keys[3] = false;
    keys[4] = false;
    mouseLocked = false;
}

Game::~Game()
{
    delete skyShader;
    delete lightingShader;
    delete skyTexture;
    delete floorTexture;
    delete grassTexture;
    delete skyMesh;
    delete floorMesh;
    delete roomMesh;
    delete player;
}

void Game::tick()
{
    player->tick(keys[0], keys[1], keys[2], keys[3], keys[4]);
}

void Game::render()
{
    glDepthMask(GL_FALSE);
    loadIdentityMatrix(viewMatrix);
    rotateYMatrix(viewMatrix, -player->yRot);
    rotateXMatrix(viewMatrix, -player->xRot);

    skyShader->use();
    skyShader->setUniformMatrix4f("projectionMatrix", projectionMatrix);
    skyShader->setUniformMatrix4f("viewMatrix", viewMatrix);
    skyTexture->bind();
    skyMesh->bind();
    skyMesh->render(0.0f, 0.0f, 0.0f);

    glDepthMask(GL_TRUE);
    loadIdentityMatrix(viewMatrix);
    translateMatrix(viewMatrix, -player->x, -player->y - 1.5f, -player->z);
    rotateYMatrix(viewMatrix, -player->yRot);
    rotateXMatrix(viewMatrix, -player->xRot);

    lightingShader->use();
    lightingShader->setUniformMatrix4f("projectionMatrix", projectionMatrix);
    lightingShader->setUniformMatrix4f("viewMatrix", viewMatrix);
    grassTexture->bind();
    floorMesh->bind();
    floorMesh->render(0.0f, 0.0f, 0.0f);
    
    // floorTexture->bind();
    // roomMesh->bind();
    // roomMesh->render(0.0f, 0.0f, 0.0f);
}

// Clear the triangles vector and return a reference to a collection of triangles near this position.
vector<Triangle*>* Game::getTriangles(float x, float y, float z)
{
    triangles.clear();
    for (unsigned int i = 0; i < floorMesh->triangleCount / 3; i++)
    {
        triangles.push_back(&floorMesh->triangles[i]);
    }
    // for (unsigned int i = 0; i < roomMesh->triangleCount / 3; i++)
    // {
    //     triangles.push_back(&roomMesh->triangles[i]);
    // }
    return &triangles;
}

void Game::keyPressed(int key)
{
    takeKey(key, true);
}

void Game::keyReleased(int key)
{
    takeKey(key, false);
}

void Game::mouseMoved(int xp, int yp)
{
    if (mouseLocked)
    {
        int xd = xp - xLast;
        int yd = yp - yLast;
        player->yRot += xd / 1024.0f;
        player->xRot += yd / 1024.0f;
        if (player->xRot < -1.5707963f) player->xRot = -1.5707963f;
        else if (player->xRot > 1.5707963f) player->xRot = 1.5707963f;
        xLast = xp;
        yLast = yp;
    }
}

void Game::takeKey(int key, bool down)
{
    switch (key)
    {
        case GLFW_KEY_W:
            keys[2] = down;
            break;
        case GLFW_KEY_A:
            keys[0] = down;
            break;
        case GLFW_KEY_S:
            keys[3] = down;
            break;
        case GLFW_KEY_D:
            keys[1] = down;
            break;
        case GLFW_KEY_SPACE:
            keys[4] = down;
            break;
        default:
            break;
    }
}