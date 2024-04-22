#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(std::string texturePath)
{
	Initialise(texturePath, false);
}

Texture::Texture(std::string texturePath, bool isBlurred)
{
	Initialise(texturePath, isBlurred);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

unsigned int Texture::GetID()
{
	return m_ID;
}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glDeleteTextures(1, &m_ID);
}

void Texture::Initialise(std::string texturePath, bool isBlurred)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	m_UniquePath = texturePath;

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char* textureData = stbi_load(EvaluatedPath().c_str(), &width, &height, &nrChannels, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (isBlurred) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_image_free(textureData);
}
