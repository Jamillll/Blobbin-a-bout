#include "Entity.h"

std::vector<Entity*> Entity::m_entityList;

Entity::Entity()
{
	m_entityList.push_back(this);
	m_ID = m_entityList.size() - 1;
}

void Entity::UpdateAll(GLFWwindow* window)
{
	for (size_t i = 0; i < m_entityList.size(); i++)
	{
		m_entityList[i]->Update(window);
	}
}

void Entity::DrawAll(Renderer& renderer)
{
	for (size_t i = 0; i < m_entityList.size(); i++)
	{
		m_entityList[i]->Draw(renderer);
	}
}

void Entity::Update(GLFWwindow* window)
{
}

void Entity::Draw(Renderer& renderer)
{
}

Entity::~Entity()
{
	
}