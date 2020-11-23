#include "Obstacle.h"

Obstacle::Obstacle(sf::Texture &tex, float x, float y):
    MainObject(x, y),
    ScorePoint(20)
{
    // define collision mask
    m_w = 32;
    m_h = 32;
    m_speed = -12.f;

    // load texture
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f), false, false);
    updateCollisionMask();
}

void Obstacle::step(float const& DELTA_TIME)
{
    m_x += ((m_speed * is::VALUE_CONVERSION) * DELTA_TIME);
    updateCollisionMask();
    updateSprite();
}
