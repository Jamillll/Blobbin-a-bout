#include "Player.h"

Player::Player(b2World& world) : Entity()
{
    b2BodyDef bodyDef;

    bodyDef.userData.pointer = this->m_ID;
    m_Tag = PLAYER;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 0.0f);
    bodyDef.fixedRotation = true; 
    m_Body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(m_Size.x / 2, m_Size.y / 2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;

    m_Body->CreateFixture(&fixtureDef);
}

void Player::Update(GLFWwindow* window)
{
    b2Vec2 moveVelocity(0, 0);

    if (glfwGetKey(window, GLFW_KEY_SPACE) && m_JumpCount > 0 && m_JumpPrimed)
    {
        m_JumpPrimed = false;
        moveVelocity.y += m_JumpPower;
        m_JumpCount--;
    }
    else if (!glfwGetKey(window, GLFW_KEY_SPACE)) m_JumpPrimed = true;

    if (glfwGetKey(window, GLFW_KEY_A) || glfwGetKey(window, GLFW_KEY_D))
    {
        if (glfwGetKey(window, GLFW_KEY_A) && m_Body->GetLinearVelocity().x > -m_MaxAcceleration)
        {
            moveVelocity.x -= m_Acceleration;
        }

        if (glfwGetKey(window, GLFW_KEY_D) && m_Body->GetLinearVelocity().x < m_MaxAcceleration)
        {
            moveVelocity.x += m_Acceleration;
        }
    }
    else m_Body->SetLinearVelocity(b2Vec2(m_Body->GetLinearVelocity().x * 0.7, m_Body->GetLinearVelocity().y));

    m_Body->SetLinearVelocity(m_Body->GetLinearVelocity() + moveVelocity);
}

void Player::Draw(Renderer &renderer)
{
    renderer.DrawRectangle(*m_Body, m_Size, m_Colour);
}

void Player::BeginContact(b2Contact* contact)
{
    unsigned int aID = contact->GetFixtureA()->GetBody()->GetUserData().pointer;
    unsigned int bID = contact->GetFixtureB()->GetBody()->GetUserData().pointer;

    if (aID != m_ID)
    {
        unsigned int temp = aID;
        aID = bID;
        bID = temp;
    }

    if (m_entityList[bID]->m_Tag == FLOOR)
    {
        m_JumpCount = m_MaxJumps;
    }
}

void Player::EndContact(b2Contact* contact)
{
}

void Player::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void Player::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

Player::~Player()
{
}
