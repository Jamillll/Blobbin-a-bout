#pragma once
#include "VAO.h"
#include "ShaderHandler.h"
#include "../Types.h"
#include "../AssetFormats/Texture2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <box2D/box2d.h>

class Renderer
{
private:
	VAO* m_VAO = nullptr;
	ShaderHandler* m_ColourShaders = nullptr;
	ShaderHandler* m_TextureShaders = nullptr;
	glm::mat4 m_MVPMatrix;
	glm::mat4 m_Projection;

public:
	Renderer();

	void ClearScreen();

	void DrawRectangle(b2Body &body, Vec2 size, Vec4 colour);
	void DrawRectangle(Rect rectangle);
	void DrawRectangle(Vec2 position, Vec2 size, Vec4 colour);

	void DrawTexture(b2Body &body, Vec2 size, Texture texture);
	void DrawTexture(Rect rectangle, Texture texture);
	void DrawTexture(Vec2 position, Vec2 size, Texture texture);

	void SetCameraPosition(Vec3 increment);

	~Renderer();
};