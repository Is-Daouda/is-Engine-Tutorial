#include "Bonus.h"

Bonus::Bonus(sf::Texture &tex, float x, float y):
    MainObject(x, y),
    Destructible(),
    ScorePoint(10),
    Step(0)
{
    m_w = 32;
    m_h = 32;
    m_speed = -15.f;
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 32, 32), sf::Vector2f(m_x, m_y), sf::Vector2f(16.f, 16.f));
}

void Bonus::step(float const &DELTA_TIME)
{
    m_x += ((m_speed * is::VALUE_CONVERSION) * DELTA_TIME);
    if (m_step == 1) m_destroy = true;
    updateSprite();
    updateCollisionMask();
}
