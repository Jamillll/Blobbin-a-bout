#include "MyGui.h"

MyGui::MyGui(GLFWwindow* window)
{
    m_Window = window;
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    ImGui::StyleColorsLight();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 450");

    m_WindowFlags |= ImGuiWindowFlags_NoTitleBar;
    m_WindowFlags |= ImGuiWindowFlags_NoMove;
    m_WindowFlags |= ImGuiWindowFlags_NoResize;
    m_WindowFlags |= ImGuiWindowFlags_NoCollapse;
    m_WindowFlags |= ImGuiWindowFlags_NoNav;
    m_WindowFlags |= ImGuiWindowFlags_NoBackground;
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

ImGuiWindowFlags MyGui::GetWantedFlags()
{
    return m_WindowFlags;
}

MyGui::~MyGui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
