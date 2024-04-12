#pragma once
#include "Entity.h"
#include "Player.h"
#include "Terrain.h"
#include "../AssetFormats/Level.h"

#include <vector>

class LevelManager : public Entity
{
private: 
	Renderer* m_Renderer = nullptr;
	Player* m_Player = nullptr;
	Vec3 m_CameraOffset = { 0, 0, 0 };

	Level m_CurrentLevel;

public:
	LevelManager(Renderer* renderer, Player* player);

	void Update(GLFWwindow* window);

	void NextLevel();
	void LoadLevel();
	void ReloadLevel();

	void TEMP_SET_LEVEL(Level levelToAdd);
	void TEMP_DELETE_LEVEL();

	~LevelManager();

private:
	void SetLevel(Level levelToAdd);
	void DeleteLevel();
};