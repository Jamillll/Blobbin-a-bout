#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
private:
	unsigned int id;

public:
	Texture(const char* texturePath);
	void BindTexture();
	unsigned int GetID();
};