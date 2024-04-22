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
	Texture(const std::string texturePath, bool isBlurred);

	void BindTexture();
	unsigned int GetID();

	~Texture();

private:
	void Initialise(std::string texturePath, bool isBlurred);
};