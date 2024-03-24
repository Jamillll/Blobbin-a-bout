#include "Entity.h"

std::vector<Entity*> Entity::m_entityList;
b2World* Entity::m_World = nullptr;

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
		std::cout << "ID: " << m_entityList[i]->m_ID << ", Tag:" << m_entityList[i]->m_Tag << std::endl;
	}

	std::cout << std::endl; 
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
	for (size_t i = m_ID + 1; i < m_entityList.size(); i++)
	{
		m_entityList[i]->m_ID--;
	}

	m_entityList.erase(m_entityList.begin() + m_ID);
}