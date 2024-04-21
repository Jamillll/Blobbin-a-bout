#include "Coin.h"

unsigned int Coin::m_CoinCount = 0;

Coin::Coin(Vec2 position, Vec2 size, const char* texturePath)
{
	AddCoinCount(1);
	m_Tag = COIN;
	m_Size = size;

	m_Texture = new Texture(texturePath);

	b2BodyDef bodyDef;
	bodyDef.position.Set(position.x, position.y);
	bodyDef.userData.pointer = this->m_ID;

	m_Body = m_World->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox(m_Size.x / 2, m_Size.y / 2);

	m_Body->CreateFixture(&box, 0.0f);
}

void Coin::Update(GLFWwindow* window)
{
	if (m_Body->IsEnabled() == false) return;

	if (isCollected)
	{
		AddCoinCount(-1);
		m_Body->SetEnabled(false);
	}
}

void Coin::Draw(Renderer& renderer)
{
	if (isCollected) return;

	renderer.DrawTexture(*m_Body, m_Size, m_Texture);
}

unsigned int Coin::GetCoinCount()
{
	return m_CoinCount;
}

Coin::~Coin()
{
	m_World->DestroyBody(m_Body);
	delete m_Texture;
}

void Coin::SetCoinCount(unsigned int newCount)
{
	if (newCount < 0) return;

	m_CoinCount = newCount;
}

void Coin::AddCoinCount(int ToAdd)
{
	int tempValue = GetCoinCount() + ToAdd;

	if (tempValue < 0) return;

	m_CoinCount = tempValue;
}
