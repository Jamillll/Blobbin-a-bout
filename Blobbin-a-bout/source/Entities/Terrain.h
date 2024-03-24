#pragma once
#include "Entity.h"
#include <box2d/box2d.h>

class Terrain : public Entity
{
private:
	Texture* m_Texture = nullptr;
	Vec2 m_Size;
	b2Body* m_Body = nullptr;

public:
	Terrain(b2World& world, Vec2 position, Vec2 size, const char* texturePath, bool isFloor);
	Terrain(b2World& world, Vec2 position, Vec2 size, const char* texturePath);

	void Update(GLFWwindow* window);
	void Draw(Renderer& renderer);

	~Terrain();

private:
	void Initialise(b2World& world, Vec2 position, Vec2 size, const char* texturePath, bool isFloor);
};