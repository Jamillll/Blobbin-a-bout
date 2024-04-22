#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <box2D/box2d.h>

#include <iostream>

#include "Types.h"
#include "Timer.h"
#include "AssetFormats/Texture2D.h"
#include "Rendering/Renderer.h"
#include "Rendering/MyGui.h"

#include "Entities/Entity.h"
#include "Entities/Player.h"
#include "Entities/Coin.h"
#include "Entities/LevelManager.h"

GLFWwindow* SetupWindow(); // Check below main function

int main()
{
    GLFWwindow* window = SetupWindow();
    if (window == nullptr) return -1;

    int frameRate = 0;
    double frameTime = 0;
    unsigned int frameCount = 0;
    double previousTime = glfwGetTime();

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
    levelManager.LoadFirstLevel();

    Texture background("AAAA.jpg", true);

    while (!glfwWindowShouldClose(window))
    {
        Timer timer(&frameTime);

        //Calculate fps
        {
            double currentTime = glfwGetTime();
            frameCount++;

            if (currentTime - previousTime >= 1.0)
            {
                frameRate = frameCount;

                frameCount = 0;
                previousTime = currentTime;
            }
        }

        renderer.ClearScreen();
        myGui.StartFrame();

        Entity::UpdateAll(window);
        world.Step(timeStep, 6, 2);

        if (myGui.ShowDebugMenu())
        {
            bool open = true;
            ImGui::Begin("Debug Menu", &open, myGui.GetWantedFlags());
            ImGui::SeparatorText("Level Navigation:");

            if (ImGui::Button("Next Level"))
            {
                levelManager.NextLevel();
            }

            if (ImGui::Button("Reload Level"))
            {
                levelManager.ReloadLevel();
            }

            ImGui::Text("Set Level by Index:");
            int levelIndex = levelManager.GetCurrentLevelIndex();
            ImGui::InputInt("##levelIndex", &levelIndex);
            if (levelIndex != levelManager.GetCurrentLevelIndex())
            {
                levelManager.SetLevel(levelIndex);
            }

            ImGui::SeparatorText("Player Info:");
            ImGui::Text("Player Position: %.1f, %.1f", player.m_Body->GetPosition().x, player.m_Body->GetPosition().y);
            ImGui::Text("Player Velocity: %.1f, %.1f", player.m_Body->GetLinearVelocity().x, player.m_Body->GetLinearVelocity().y);

            ImGui::SeparatorText("Performance Info:");
            ImGui::Text("Fps (Frames Per Second): %d", frameRate);
            ImGui::Text("Frame Time: %f", frameTime);

            int coinCount = 0;
            for (size_t i = 0; i < Entity::m_entityList.size(); i++)
            {
                if (Entity::m_entityList[i]->m_Tag == Entity::COIN)
                {
                    coinCount = Coin::GetCoinCount();
                    goto exitLoop;
                }
            }

        exitLoop:
            ImGui::Text("CoinCount: %d", coinCount);

            ImGui::End();
        }

        renderer.DrawTexture({ 0, 0 }, {32, 20}, &background);
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

    glfwSwapInterval(1);
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