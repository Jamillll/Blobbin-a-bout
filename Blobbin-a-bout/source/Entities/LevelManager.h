#pragma once
#include "Entity.h"
#include "Player.h"

#include <vector>

struct Level
{
	Vec2 spawnPoint;
	std::vector<Entity*> contents;
};

class LevelManager : public Entity
{
private: 
	Renderer* m_Renderer = nullptr;
	Player* m_Player = nullptr;
	Vec3 m_CameraOffset = { 0, 0, 0 };

	std::vector<Level> m_Levels;
	unsigned int m_CurrentLevel = 0;

public:
	LevelManager(Renderer* renderer, Player* player);

	void Update(GLFWwindow* window);

	void NextLevel();
	void ReloadLevel();

	void TEMP_ADD_LEVEL(Vec2 spawnPoint, std::vector<Entity*> contents);
	void TEMP_ADD_LEVEL(Level levelToAdd);

	~LevelManager();

private:
	void AddLevel(Vec2 spawnPoint, std::vector<Entity*> contents);
	void AddLevel(Level levelToAdd);
};