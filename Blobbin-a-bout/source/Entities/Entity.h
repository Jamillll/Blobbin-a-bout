#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "..\Rendering\Renderer.h"

class Entity
{
public:
	static std::vector<Entity*> m_entityList;
	static b2World* m_World;

	unsigned int m_ID;
	unsigned int m_Tag = ENTITY;

	enum Tag
	{
		ENTITY = 0,
		PLAYER = 1,
		TERRAIN = 2,
		FLOOR = 3,
		MANAGER = 4,
	};

	Entity();

	static void UpdateAll(GLFWwindow* window);
	static void DrawAll(Renderer& renderer);

	virtual void Update(GLFWwindow* window);
	virtual void Draw(Renderer& renderer);

	virtual ~Entity();
};
