#pragma once
#include "Entity.h"

class Coin : public Entity 
{
private:
	static unsigned int m_CoinCount;

public:
	Texture* m_Texture = nullptr;
	b2Body* m_Body = nullptr;
	bool isCollected = false;
	Vec2 m_Size;

	Coin(Vec2 position, Vec2 size, const char* texturePath);

	void Update(GLFWwindow* window);
	void Draw(Renderer& renderer);

	static unsigned int GetCoinCount();

	~Coin();

private:
	void SetCoinCount(unsigned int newCount);
	void AddCoinCount(int ToAdd);
};