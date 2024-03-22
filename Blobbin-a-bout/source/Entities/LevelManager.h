#pragma once
#include "Entity.h"
#include "Player.h"

class LevelManager : public Entity
{
private: 
	Renderer* m_Renderer = nullptr;
	Player* m_Player = nullptr;
	Vec3 m_CameraOffset = { 0, 0, 0 };

public:
	LevelManager(Renderer* renderer, Player* player);

	void Update(GLFWwindow* window);

	~LevelManager();
};