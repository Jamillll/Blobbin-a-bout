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

void LevelManager::TEMP_SET_LEVEL(Level levelToAdd)
{
	SetLevel(levelToAdd);
}

void LevelManager::TEMP_DELETE_LEVEL()
{
	DeleteLevel();
}

void LevelManager::SetLevel(Level levelToAdd)
{
	m_CurrentLevel = levelToAdd;
}

void LevelManager::DeleteLevel()
{
	for (size_t i = 0; i < m_CurrentLevel.contents.size(); i++)
	{
		delete m_CurrentLevel.contents[i];
	}
}

LevelManager::~LevelManager()
{
}
