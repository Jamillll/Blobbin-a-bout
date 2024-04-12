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

void LevelManager::LoadLevel()
{
}

void LevelManager::ReloadLevel()
{
}

void LevelManager::SetLevel(Level levelToAdd)
{
	m_CurrentLevel = levelToAdd;
	m_Player->m_Body->SetTransform(b2Vec2(m_CurrentLevel.spawnPoint.x, m_CurrentLevel.spawnPoint.y), 0);
}

LevelManager::~LevelManager()
{
}
