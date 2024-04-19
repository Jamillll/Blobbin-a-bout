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

void LevelManager::LoadFirstLevel()
{
	SetLevel(0);
}

void LevelManager::NextLevel()
{
	std::vector<std::string> levelNames = GetLevelList();

	if (levelNames.size() - 1 == m_CurrentLevelIndex) return;

	m_CurrentLevelIndex++;
	std::string uniquePath = "Levels/" + levelNames[m_CurrentLevelIndex] + ".txt";

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
	m_Player->m_Body->SetLinearVelocity(b2Vec2_zero);
	m_Player->m_Body->SetTransform(b2Vec2(m_CurrentLevel->spawnPoint.x, m_CurrentLevel->spawnPoint.y), 0);
}

void LevelManager::SetLevel(int index)
{
	std::vector<std::string> levelNames = GetLevelList();

	if (index > levelNames.size() - 1 || index < 0) return;

	m_CurrentLevelIndex = index;
	std::string uniquePath = "Levels/" + levelNames[index] + ".txt";

	SetLevel(uniquePath.data());
}

int LevelManager::GetCurrentLevelIndex()
{
	return m_CurrentLevelIndex;
}

LevelManager::~LevelManager()
{
}

std::vector<std::string> LevelManager::GetLevelList()
{
	using namespace std;

	fstream file(m_CurrentLevel->m_BasePath + "Levels\\!LevelList.txt");
	vector<string> levelNames;
	string input;

	while (getline(file, input))
	{
		levelNames.push_back(input);
	}
	file.close();

	return levelNames;
}
