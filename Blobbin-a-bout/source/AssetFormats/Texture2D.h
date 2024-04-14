#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Asset.h"

class Texture : public Asset
{
private:
	unsigned int m_ID;

public:
	Texture(const std::string texturePath);

	void BindTexture();
	unsigned int GetID();

	~Texture();
};