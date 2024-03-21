#pragma once
#include "VAO.h"
#include "Texture2D.h"
#include "ShaderHandler.h"
#include "../Types.h"

#include <algorithm>
#include <vector>

class Rectangle
{
private:
	Vec2 m_Position;
	Vec2 m_Size;
	Vec4 m_Colour;

	VAO* m_VAO = nullptr;
	ShaderHandler* m_Shaders = nullptr;

public:
	Rectangle(Vec2 position, Vec2 size, Vec4 colour)
	{
		m_Position = position;
		m_Size = size;
		size = { size.x / 2, size.y / 2 };
		m_Colour = colour;

		Vec4 vertices[] =
		{
			{ (m_Position.x - size.x), (m_Position.y + size.y), 1.0f, 1.0f }, m_Colour, // top left
			{ (m_Position.x + size.x), (m_Position.y + size.y), 1.0f, 1.0f }, m_Colour, // top right
			{ (m_Position.x - size.x), (m_Position.y - size.y), 1.0f, 1.0f }, m_Colour, // bottom left
			{ (m_Position.x + size.x), (m_Position.y - size.y), 1.0f, 1.0f }, m_Colour, // bottom right
		};

		unsigned int indicesCount = 6;
		unsigned int indices[] =
		{
			0, 1, 3,
			0, 2, 3
		};

		m_VAO = new VAO;
		m_VAO->WriteToVertexBuffer(vertices, sizeof(vertices));
		m_VAO->WriteToIndexBuffer(indices, indicesCount);
		m_VAO->AddVertexAttribute(4, GL_FLOAT, sizeof(float), false, sizeof(Vec4) * 2);
		m_VAO->AddVertexAttribute(4, GL_FLOAT, sizeof(float), false, sizeof(Vec4) * 2);

		m_Shaders = new ShaderHandler("source\\shaders\\basicVertex.shader", "source\\shaders\\basicFrag.shader");

		glm::mat4 projection = glm::ortho(0.0f, 1000.0f, 0.0f, 600.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

		glm::mat4 mvp = projection * view;

		m_Shaders->setUniformMat4f("u_MVP", mvp);
	}

	void SetPosition(Vec2 newPosition)
	{
		m_Position = newPosition;
		Vec2 size = { m_Size.x / 2, m_Size.y / 2 };

		Vec4 vertices[] =
		{
			{ (m_Position.x - size.x), (m_Position.y + size.y), 1.0f, 1.0f }, m_Colour, // top left
			{ (m_Position.x + size.x), (m_Position.y + size.y), 1.0f, 1.0f }, m_Colour, // top right
			{ (m_Position.x - size.x), (m_Position.y - size.y), 1.0f, 1.0f }, m_Colour, // bottom left
			{ (m_Position.x + size.x), (m_Position.y - size.y), 1.0f, 1.0f }, m_Colour, // bottom right
		};

		m_VAO->WriteToVertexBuffer(vertices, sizeof(vertices));
	}

	Vec2 GetPosition()
	{
		return m_Position;
	}

	void Draw()
	{
		m_Shaders->UseShaders();
		m_VAO->DrawVAO();
	}

	~Rectangle()
	{
		delete m_VAO;
		delete m_Shaders;
	}
};