#include "Timer.h"
#include <GLFW/glfw3.h>

Timer::Timer(double* scopeTime)
{
	m_ScopeTime = scopeTime;
	m_StartTime = glfwGetTime();
}

Timer::~Timer()
{
	*m_ScopeTime = glfwGetTime() - m_StartTime;
}
