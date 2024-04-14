#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <box2D/box2d.h>

#include "Types.h"
#include "AssetFormats/Texture2D.h"
#include "Rendering/Renderer.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/Terrain.h"
#include "Entities/LevelManager.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1000, 600, "Blobbin a'bout", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    b2Vec2 gravity(0.001f, -40.0f);
    float timeStep = 1.0f / 60.0f;
    b2World world(gravity);

    Entity::m_World = &world;

    Player player(world);
    world.SetContactListener(&player);

    Renderer renderer;
    renderer.SetClearColour({ 0.5f, 0.75f, 0.9f});

    LevelManager levelManager(&renderer, &player);
    levelManager.SetLevel("Levels/TestLevel.txt");

    bool a = false;
    while (!glfwWindowShouldClose(window))
    {
        renderer.ClearScreen();

        if (glfwGetKey(window, GLFW_KEY_5) && !a)
        {
            levelManager.NextLevel();
            a = true;
        }
        if (!glfwGetKey(window, GLFW_KEY_5) && a)
        {
            a = false;
        }

        Entity::UpdateAll(window);
        world.Step(timeStep, 6, 2);

        Entity::DrawAll(renderer);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}