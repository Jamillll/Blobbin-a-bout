#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <box2D/box2d.h>

#include "Types.h"
#include "Rendering/Texture2D.h"
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
    glClearColor(0.5f, 0.75f, 0.9f, 1.0f);

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
    LevelManager levelManager(&renderer, &player);

    Level testLevel;
    {
        testLevel.spawnPoint = { 0, 0 };

        testLevel.contents.push_back(new Terrain(world, { 0, -10 }, { 32, 10 }, "container.jpg"));
        testLevel.contents.push_back(new Terrain(world, { 0, -5 }, { 32, 1 }, "wall.jpg", true));
        testLevel.contents.push_back(new Terrain(world, { -8, 0 }, { 10, 3 }, "container.jpg"));
    }

    levelManager.TEMP_SET_LEVEL(testLevel);

    while (!glfwWindowShouldClose(window))
    {
        renderer.ClearScreen();

        Entity::UpdateAll(window);
        Entity::DrawAll(renderer);

        world.Step(timeStep, 6, 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}