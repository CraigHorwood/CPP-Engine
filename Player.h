#ifndef _PLAYER_H
#define _PLAYER_H

#include "Mesh.h"

class Game;

class Player
{
public:
    Player(Game*, float, float, float);
    ~Player();
    void tick(bool, bool, bool, bool, bool);
    float x, y, z;
    float xVel, yVel, zVel;
    float xRot, yRot;
    bool onGround, wasOnGround;
private:
    void move();
    void clipFloor(Triangle*);
    void clipWall(Triangle*);
    void clipCeiling(Triangle*);
    bool inTriangle(float, float, float, float, float, float, float, float, bool);
    Game* game;
protected:
};

#endif