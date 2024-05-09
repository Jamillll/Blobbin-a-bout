#pragma once
#include "Entity.h"
#include "Player.h"
#include "../AssetFormats/Level.h"

#include <vector>

class LevelManager : public Entity
{
private:
	Renderer* m_Renderer = nullptr;
	Player* m_Player = nullptr;
	Vec3 m_CameraOffset = { 0, 0, 0 };

	Level* m_CurrentLevel = nullptr;
	int m_CurrentLevelIndex = 0;

public:
	LevelManager(Renderer* renderer, Player* player);

	void Update(GLFWwindow* window);

	void LoadFirstLevel();
	void LoadWin();
	void LoadLose();
	void LoadGameOver();

	void NextLevel();
	void ReloadLevel();

	void SetLevel(const char* levelToAdd);
	void SetLevel(int index);

	int GetCurrentLevelIndex();

	~LevelManager();

private:

	std::vector<std::string> GetLevelList();
};