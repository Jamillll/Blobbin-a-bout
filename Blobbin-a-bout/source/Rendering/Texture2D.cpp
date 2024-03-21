#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::string Texture::m_BasePath = "C:\\Programs\\Blobbin-a-bout\\Blobbin-a-bout\\Assets\\";

Texture::Texture(std::string texturePath)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	std::string fullPath = m_BasePath + texturePath;

	int width, height, nrChannels;
	unsigned char* textureData = stbi_load(fullPath.c_str() , &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

unsigned int Texture::GetID()
{
	return m_ID;
}