#include <stdio.h>
#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Game.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

using namespace std;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Game* game = (Game*) glfwGetWindowUserPointer(window);
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
        {
            if (game->mouseLocked)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                game->mouseLocked = false;
            }
        }
        else game->keyPressed(key);
    }
    else if (action == GLFW_RELEASE) game->keyReleased(key);
}

void mouseCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        Game* game = (Game*) glfwGetWindowUserPointer(window);
        if (!game->mouseLocked)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            game->xLast = (int) x;
            game->yLast = (int) y;
            game->mouseLocked = true;
        }
    }
}

void mouseMotionCallback(GLFWwindow* window, double x, double y)
{
    Game* game = (Game*) glfwGetWindowUserPointer(window);
    game->mouseMoved((int) x, (int) y);
}

int main(int argc, char* argv[])
{
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW." << endl;
        return 1;
    }
    // glfwWindowHint(GLFW_SAMPLES, 4);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C++ Demo", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window." << endl;
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        cout << "Failed to initialise GLEW." << endl;
        glfwTerminate();
        return 1;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    Game game;
    glfwSetWindowUserPointer(window, &game);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseCallback);
    glfwSetCursorPosCallback(window, mouseMotionCallback);

    glfwSetTime(0.0);
    double then = glfwGetTime();
    double passedTime = 0.0;
    const double secondsPerFrame = 1.0 / 60.0;

    while (glfwWindowShouldClose(window) == 0)
    {
        double now = glfwGetTime();
        passedTime += now - then;
        then = now;
        while (passedTime > 0.0)
        {
            passedTime -= secondsPerFrame;
            game.tick();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}