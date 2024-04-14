#pragma once
#include <GLFW/glfw3.h>
#include "../vendor/imgui/imgui.h"
#include "../vendor/imgui/imgui_impl_glfw.h"
#include "../vendor/imgui/imgui_impl_opengl3.h"

class MyGui
{
private:
	GLFWwindow* m_Window;
	bool m_DebugMenu = false;
	bool m_PressPrimed = true;

public:
	MyGui(GLFWwindow* window);

	void StartFrame();
	void Render();
	bool ShowDebugMenu();

	~MyGui();
};