#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <box2D/box2d.h>

#include <iostream>

#include "Types.h"
#include "AssetFormats/Texture2D.h"
#include "Rendering/Renderer.h"
#include "Rendering/MyGui.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/Terrain.h"
#include "Entities/LevelManager.h"

GLFWwindow* SetupWindow(); // Check below main function

int main()
{
    GLFWwindow* window = SetupWindow();
    if (window == nullptr) return -1;

    b2Vec2 gravity(0.001f, -40.0f);
    float timeStep = 1.0f / 60.0f;
    b2World world(gravity);

    Entity::m_World = &world;

    Player player(world);
    world.SetContactListener(&player);

    Renderer renderer;
    MyGui myGui(window);
    renderer.SetClearColour({ 0.5f, 0.75f, 0.9f});

    LevelManager levelManager(&renderer, &player);
    levelManager.SetLevel("Levels/TestLevel.txt");

    while (!glfwWindowShouldClose(window))
    {
        renderer.ClearScreen();
        myGui.StartFrame();

        if (myGui.ShowDebugMenu())
        {
            ImGui::Begin("Debug Menu");
            if (ImGui::Button("Next Level"))
            {
                levelManager.NextLevel();
            }
            ImGui::End();
        }

        Entity::UpdateAll(window);
        world.Step(timeStep, 6, 2);

        Entity::DrawAll(renderer);
        myGui.Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* SetupWindow()
{
    if (!glfwInit())
        return nullptr;

    GLFWwindow* window = glfwCreateWindow(1000, 600, "Blobbin a'bout", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return nullptr;
    }

    return window;
}