#include "Terrain.h"

void Terrain::Initialise(b2World& world, Vec2 position, Vec2 size, const char* texturePath, bool isFloor)
{
    m_Texture = new Texture(texturePath);
    m_Size = size;

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(position.x, position.y);
    groundBodyDef.userData.pointer = this->m_ID;
    
    if (isFloor) m_Tag = FLOOR;
    else m_Tag = TERRAIN;

    m_Body = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(m_Size.x / 2, m_Size.y / 2);

    m_Body->CreateFixture(&groundBox, 0.0f);
}

Terrain::Terrain(b2World& world, Vec2 position, Vec2 size, const char* texturePath, bool isFloor)
{
    Initialise(world, position, size, texturePath, isFloor);
}

Terrain::Terrain(b2World& world, Vec2 position, Vec2 size, const char* texturePath)
{
    Initialise(world, position, size, texturePath, false);
}

void Terrain::Update(GLFWwindow* window)
{
}

void Terrain::Draw(Renderer& renderer)
{
    renderer.DrawTexture(*m_Body, m_Size, *m_Texture);
}

Terrain::~Terrain()
{
    delete m_Texture;
}