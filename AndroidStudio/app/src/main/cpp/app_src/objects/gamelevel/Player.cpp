#include "Player.h"

Player::Player(GameKeyData &gameKey):
    MainObject(),
    Health(3),
    HurtEffect(m_sprParent),
    m_gameKey(gameKey)
{
    // define collision mask
    m_w = 40;
    m_h = 40;
    m_isActive = true;

    // initialize collision mask
    updateCollisionMask();
}

void Player::loadResources(sf::Texture &tex)
{
    is::createSprite(tex, m_sprParent, sf::IntRect(0, 0, 48, 48), sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
}

void Player::step(float const &DELTA_TIME)
{
    if (m_isActive)
    {
        // allow accelerate / decelerate player
        if (m_gameKey.m_keyBPressed) m_speed = 0.f;
        else if (m_gameKey.m_keyAPressed) m_speed = 200.f;

        // move
        float const SPEED(2.f);
        m_hsp = 0.f;
        m_vsp = 0.f;
        if (m_gameKey.m_keyRightPressed)      m_hsp = SPEED;
        else if (m_gameKey.m_keyLeftPressed)  m_hsp = -SPEED;
        else if (m_gameKey.m_keyDownPressed)  m_vsp = SPEED;
        else if (m_gameKey.m_keyUpPressed)    m_vsp = -SPEED;

        // animation
        m_frame += (0.33f * is::VALUE_CONVERSION) * DELTA_TIME; // image speed
        setFrame(0.f, 3.6f);

        // update collision mask (position, size, ...)
        updateCollisionMask();

        // update object position
        m_x += (m_hsp * is::VALUE_CONVERSION) * DELTA_TIME;
        m_y += (m_vsp * is::VALUE_CONVERSION) * DELTA_TIME;
    }
    else m_frame = 0.f;
    is::setFrame(m_sprParent, m_frame, 4, 48, 48, 48); // update sprite and animation
    updateSprite();
    hurtStep(DELTA_TIME);
}
