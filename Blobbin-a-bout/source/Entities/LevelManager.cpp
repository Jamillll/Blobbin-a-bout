#include "LevelManager.h"

LevelManager::LevelManager(Renderer* renderer, Player* player)
{
	m_Renderer = renderer;
	m_Player = player;
	m_Tag = MANAGER;
}

void LevelManager::Update(GLFWwindow* window)
{
	m_CameraOffset.x -= 0.01f;
	m_Renderer->SetCameraPosition({ -m_Player->m_Body->GetPosition().x, 0, 0 });
}

void LevelManager::NextLevel()
{
}

void LevelManager::ReloadLevel()
{
}

void LevelManager::TEMP_ADD_LEVEL(Vec2 spawnPoint, std::vector<Entity*> contents)
{
	AddLevel(spawnPoint, contents);
}

void LevelManager::TEMP_ADD_LEVEL(Level levelToAdd)
{
	AddLevel(levelToAdd);
}

void LevelManager::AddLevel(Vec2 spawnPoint, std::vector<Entity*> contents)
{
	AddLevel({spawnPoint, contents});
}

void LevelManager::AddLevel(Level levelToAdd)
{
	m_Levels.push_back(levelToAdd);
}

LevelManager::~LevelManager()
{
}
