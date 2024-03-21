#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture
{
private:
	static std::string m_BasePath;

	unsigned int m_ID;

public:
	Texture(const std::string texturePath);
	void BindTexture();
	unsigned int GetID();
};