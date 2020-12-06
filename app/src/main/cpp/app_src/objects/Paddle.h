#ifndef Paddle_H_INCLUDED
#define Paddle_H_INCLUDED

#include "../../isEngine/system/display/GameDisplay.h"
#include "Ball.h"

class Paddle : public is::MainObject
{
public:
    Paddle(float x, float y, is::GameDisplay *scene):
        MainObject(x, y),
        m_scene(scene)
    {
        m_strName = "Paddle"; // We give the name of the object (very important)
        is::createSprite(scene->GRMgetTexture("paddle"), m_sprParent, sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
        setRectangleMask(getTextureWidth(), getTextureHeight()); // Always set the collision mask if you want to do collision tests
        m_speed = 3.f; // Paddle movement speed (in pixels)
    }

    void step(float const &DELTA_TIME)
    {
        // This line tests the collision between the ball and the Paddle
        if (auto ball = static_cast<Ball*>(m_scene->SDMgetObject("Ball")); ball != nullptr)
        {
            if (placeMetting(0, 0, ball)) // If the ball hits the object (paddle)
            {
                if (ball->getVsp() > 0.f) // If the ball goes down
                {
                    if (ball->getX() < m_x + 20.f) ball->setHsp(-ball->getSpeed()); // If it is completely to the left of the Paddle deviated to the left
                    if (ball->getX() > m_x + 40.f) ball->setHsp(ball->getSpeed()); // If it is completely to the right of the paddle deviated to the right

                    ball->setVsp(-ball->getVsp()); // Bounce up (represents a negative value for vertical speed)
                    m_scene->GSMplaySound("bounce_paddle"); // Play the sound bounce on Paddle
                }
            }

            if (static_cast<int>(ball->getVsp()) != 0) // Before moving the Paddle the Ball must be thrown first
            {
                if (m_x > m_w / 2.f // We check if the Paddle has not passed the left side of the playing field before moving it
                     && (m_scene->getGameSystem().keyIsPressed(is::GameConfig::KEY_LEFT) // When press the left key

                    // Move Paddle with screen when user touch or clic left corner (also works on android)
                    || (m_scene->getGameSystem().isPressed(is::GameSystem::MOUSE) && m_scene->getCursor().x < 320.f))
                    )
                    m_x -= m_speed * is::VALUE_CONVERSION * DELTA_TIME; // We move the Paddle to the left
                else if (m_x + m_w + 32.f < m_scene->getSceneWidth() // We check if the Paddle has not passed the right side of the playing field before moving it
                         && (m_scene->getGameSystem().keyIsPressed(is::GameConfig::KEY_RIGHT)  // When press the right key
                    // Move Paddle with screen when user touch right corner (also works on android)
                    || (m_scene->getGameSystem().isPressed(is::GameSystem::MOUSE) && m_scene->getCursor().x > 320.f)))
                    m_x += m_speed * is::VALUE_CONVERSION * DELTA_TIME; // We move the Paddle to the right
            }
        }
        updateSprite();
        updateCollisionMask();
    }

private:
    is::GameDisplay *m_scene;
};

#endif // Paddle_H_INCLUDED
