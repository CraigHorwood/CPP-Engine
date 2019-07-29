#include "Player.h"
#include "Game.h"
#include "Mesh.h"
#include <math.h>
#include <vector>

using namespace std;

Player::Player(Game* game, float x, float y, float z)
{
    this->game = game;
    this->x = x;
    this->y = y;
    this->z = z;
    xVel = 0.0f;
    yVel = 0.0f;
    zVel = 0.0f;
    xRot = 0.0f;
    yRot = 0.0f;
    onGround = false;
    wasOnGround = false;
}

Player::~Player()
{
}

void Player::move()
{
    wasOnGround = onGround;
    onGround = false;
    x += xVel;
    y += yVel;
    z += zVel;
    vector<Triangle*>* triangles = game->getTriangles(x, y, z);
    for (unsigned int i = 0; i < triangles->size(); i++)
    {
        Triangle* t = (*triangles)[i];
        if (t->yNormal > 0.0625f) clipFloor(t);
        else if (t->yNormal < -0.0625f) clipCeiling(t);
        else clipWall(t);
    }
}

void Player::clipFloor(Triangle* t)
{
    if (inTriangle(x, z, t->x0, t->z0, t->x1, t->z1, t->x2, t->z2, false))
    {
        float yClip = (-t->d - t->xNormal * x - t->zNormal * z) / t->yNormal;
        float yd = y - yClip;
        float ydMax = wasOnGround ? 0.25f : 0.0f;
        if (yd < ydMax && yd > -0.25f)
        {
            y = yClip;
            yVel = 0.0f;
            onGround = true;
        }
    }
}

void Player::clipWall(Triangle* t)
{
    if (t->xNormal < -0.7071068f || t->xNormal > 0.7071068f)
    {
        if  (inTriangle(z, y + 1.0f, t->z0, t->y0, t->z1, t->y1, t->z2, t->y2, t->xNormal < 0.0f))
        {
            float xClip = (-t->d - t->yNormal * y - t->zNormal * z) / t->xNormal;
            float xd = x - xClip;
            if (xd < 0.5f && xd > -0.5f)
            {
                x = xClip + t->xNormal * 0.5f;
                xVel = 0.0f;
            }
        }
    }
    else if (inTriangle(y + 1.0f, x, t->y0, t->x0, t->y1, t->x1, t->y2, t->x2, t->zNormal < 0.0f))
    {
        float zClip = (-t->d - t->xNormal * x - t->yNormal * y) / t->zNormal;
        float zd = z - zClip;
        if (zd < 0.5f && zd > -0.5f)
        {
            z = zClip + t->zNormal * 0.5f;
            zVel = 0.0f;
        }
    }
}

void Player::clipCeiling(Triangle* t)
{
}

bool Player::inTriangle(float xPoint, float yPoint, float x0, float y0, float x1, float y1, float x2, float y2, bool negative)
{
    float sign = negative ? -1.0f : 1.0f;
    if (((y1 - y0) * (xPoint - x0) - (x1 - x0) * (yPoint - y0)) * sign < 0.0f) return false;
    if (((y2 - y1) * (xPoint - x1) - (x2 - x1) * (yPoint - y1)) * sign < 0.0f) return false;
    return (y0 - y2) * (xPoint - x2) - (x0 - x2) * (yPoint - y2) >= 0.0f;
}

void Player::tick(bool left, bool right, bool up, bool down, bool jump)
{
    const float speed = 0.0078125f;
    float xImpulse = 0.0f;
    float zImpulse = 0.0f;
    if (left) xImpulse = -speed;
    else if (right) xImpulse = speed;
    if (up) zImpulse = -speed;
    else if (down) zImpulse = speed;
    float rCos = cosf(yRot);
    float rSin = sinf(yRot);
    xVel += xImpulse * rCos - zImpulse * rSin;
    zVel += zImpulse * rCos + xImpulse * rSin;
    if (jump && onGround)
    {
        yVel = 0.125f;
        onGround = false;
        wasOnGround = false;
    }
    move();
    xVel *= 0.875f;
    zVel *= 0.875f;
    yVel -= 0.0078125f;
}