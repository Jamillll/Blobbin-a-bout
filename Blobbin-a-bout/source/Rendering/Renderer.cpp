#include "Renderer.h"

Renderer::Renderer()
{
	m_VAO = new VAO;
	m_VAO->AddVertexAttribute(4, GL_FLOAT, sizeof(float), false, sizeof(Vec4) * 2);
	m_VAO->AddVertexAttribute(4, GL_FLOAT, sizeof(float), false, sizeof(Vec4) * 2);

	m_ColourShaders = new ShaderHandler("source\\Rendering\\shaders\\basicVertex.shader", "source\\Rendering\\shaders\\basicFrag.shader");
	m_TextureShaders = new ShaderHandler("source\\Rendering\\shaders\\textureVertex.shader", "source\\Rendering\\shaders\\textureFrag.shader");

	m_Projection = glm::ortho(-16.0f, 16.0f, -10.0f, 10.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	m_MVPMatrix = m_Projection * view;

	m_ColourShaders->setUniformMat4f("u_MVP", m_MVPMatrix);
	m_TextureShaders->setUniformMat4f("u_MVP", m_MVPMatrix);
	m_TextureShaders->setTextureUniform("texture2D", 0);
}

void Renderer::ClearScreen()
{
	while (true)
	{
		GLenum error = glGetError();

		if (error == GL_NO_ERROR)
			break;

		std::cout << error << std::endl;
	}

	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::DrawRectangle(b2Body &body, Vec2 size, Vec4 colour)
{
	DrawRectangle({ body.GetPosition().x, body.GetPosition().y }, size, colour);
}

void Renderer::DrawRectangle(Rect rectangle)
{
	DrawRectangle(rectangle.position, rectangle.size, rectangle.colour);
}

void Renderer::DrawRectangle(Vec2 position, Vec2 size, Vec4 colour)
{
	size = { size.x / 2, size.y / 2 };

	Vec4 vertices[] =
	{
		{ (position.x - size.x), (position.y + size.y), 1.0f, 1.0f }, colour, // top left
		{ (position.x + size.x), (position.y + size.y), 1.0f, 1.0f }, colour, // top right
		{ (position.x - size.x), (position.y - size.y), 1.0f, 1.0f }, colour, // bottom left
		{ (position.x + size.x), (position.y - size.y), 1.0f, 1.0f }, colour, // bottom right
	};

	unsigned int indicesCount = 6;
	unsigned int indices[] =
	{
		0, 1, 3,
		0, 2, 3
	};

	m_VAO->WriteToVertexBuffer(vertices, sizeof(vertices));
	m_VAO->WriteToIndexBuffer(indices, indicesCount);

	m_ColourShaders->UseShaders();
	m_VAO->DrawVAO();
}

void Renderer::DrawTexture(b2Body &body, Vec2 size, Texture texture)
{
	DrawTexture({ body.GetPosition().x, body.GetPosition().y }, size, texture);
}

void Renderer::DrawTexture(Rect rectangle, Texture texture)
{
	DrawTexture(rectangle.position, rectangle.size, texture);
}

void Renderer::DrawTexture(Vec2 position, Vec2 size, Texture texture)
{
	size = { size.x / 2, size.y / 2 };

	Vec4 vertices[] =
	{
		{ (position.x - size.x), (position.y + size.y), 1.0f, 1.0f }, { 0.0f, 1.0f, 0, 0 }, // top left
		{ (position.x + size.x), (position.y + size.y), 1.0f, 1.0f }, { 1.0f, 1.0f, 0, 0 }, // top right
		{ (position.x - size.x), (position.y - size.y), 1.0f, 1.0f }, { 0.0f, 0.0f, 0, 0 }, // bottom left
		{ (position.x + size.x), (position.y - size.y), 1.0f, 1.0f }, { 1.0f, 0.0f, 0, 0 }, // bottom right
	};

	unsigned int indicesCount = 6;
	unsigned int indices[] =
	{
		0, 1, 3,
		0, 2, 3
	};

	glActiveTexture(GL_TEXTURE0);
	texture.BindTexture();

	m_VAO->WriteToVertexBuffer(vertices, sizeof(vertices));
	m_VAO->WriteToIndexBuffer(indices, indicesCount);

	m_TextureShaders->UseShaders();
	m_VAO->DrawVAO();
}

void Renderer::SetCameraPosition(Vec3 increment)
{
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(increment.x, increment.y, increment.z));
	m_MVPMatrix = m_Projection * view;
	m_ColourShaders->setUniformMat4f("u_MVP", m_MVPMatrix);
	m_TextureShaders->setUniformMat4f("u_MVP", m_MVPMatrix);
}

Renderer::~Renderer()
{
	delete m_VAO;
	delete m_ColourShaders;
	delete m_TextureShaders;
}