#include "MyGui.h"

MyGui::MyGui(GLFWwindow* window)
{
    m_Window = window;
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
}

void MyGui::StartFrame()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (glfwGetKey(m_Window, GLFW_KEY_F3) && m_PressPrimed)
    {
        if (glfwGetKey(m_Window, GLFW_KEY_F3) && !m_DebugMenu)
        {
            m_DebugMenu = true;
        }
        else if (glfwGetKey(m_Window, GLFW_KEY_F3) && m_DebugMenu)
        {
            m_DebugMenu = false;
        }

        m_PressPrimed = false;
    }
    else if (!glfwGetKey(m_Window, GLFW_KEY_F3))
    {
        m_PressPrimed = true;
    }
}

void MyGui::Render()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool MyGui::ShowDebugMenu()
{
    return m_DebugMenu;
}

MyGui::~MyGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
