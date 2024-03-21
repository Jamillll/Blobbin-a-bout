#include "Texture2D.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char* texturePath)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	int width, height, nrChannels;
	unsigned char* textureData = stbi_load(texturePath, &width, &height, &nrChannels, 0);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(textureData);
}

void Texture::BindTexture()
{
	glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int Texture::GetID()
{
	return id;
}