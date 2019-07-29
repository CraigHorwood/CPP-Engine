#ifndef _GAME_H
#define _GAME_H

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"
#include "Player.h"
#include <vector>

class Game
{
public:
    Game();
    ~Game();
    void tick();
    void render();
    void keyPressed(int);
    void keyReleased(int);
    void mouseMoved(int, int);
    std::vector<Triangle*>* getTriangles(float, float, float);
    bool mouseLocked;
    int xLast, yLast;
private:
    void takeKey(int, bool);
    Shader* lightingShader;
    Shader* skyShader;
    Texture* skyTexture;
    Texture* floorTexture;
    Texture* grassTexture;
    Mesh* skyMesh;
    Mesh* floorMesh;
    Mesh* roomMesh;
    float projectionMatrix[16];
    float viewMatrix[16];
    Player* player;
    bool keys[5];
    std::vector<Triangle*> triangles;
protected:
};

#endif