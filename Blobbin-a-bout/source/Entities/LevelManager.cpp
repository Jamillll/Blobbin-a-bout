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
	std::string uniquePath = m_CurrentLevel->m_UniquePath;
	int beforeExtention = 5;

	uniquePath[uniquePath.length() - beforeExtention]++;

	SetLevel(uniquePath.data());
}

void LevelManager::ReloadLevel()
{
	std::string uniquePath = m_CurrentLevel->m_UniquePath;

	SetLevel(uniquePath.data());

}

void LevelManager::SetLevel(const char* levelToAdd)
{
	if (m_CurrentLevel != nullptr) delete m_CurrentLevel;

	// TODO: Add a fancy transition animation maybe??

	m_CurrentLevel = new Level(levelToAdd);
	m_Player->m_Body->SetTransform(b2Vec2(m_CurrentLevel->spawnPoint.x, m_CurrentLevel->spawnPoint.y), 0);
}

LevelManager::~LevelManager()
{
}
