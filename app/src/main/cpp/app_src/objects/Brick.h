#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include "../../isEngine/system/display/GameDisplay.h"
#include "Ball.h"

class Brick : public is::MainObject
{
public:
    Brick(float x, float y, is::GameDisplay *scene):
        MainObject(x, y),
        m_scene(scene)
    {
        m_strName = "Brick"; // We give the name of the object (very important)
        is::createSprite(scene->GRMgetTexture("brick"), m_sprParent, sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));
        setRectangleMask(getTextureWidth(), getTextureHeight()); // Always set the collision mask if you want to do collision tests
    }

    void step(float const &DELTA_TIME)
    {
        // This following line tests the collision between the ball and the brick
        if (auto ball = static_cast<Ball*>(m_scene->SDMgetObject("Ball")); ball != nullptr)
        {
            if (placeMetting(0, 0, ball)) // If the ball hits the object (brick)
            {
                // If the Ball is below the object, bounce down
                if (ball->getY() > (m_y + m_h) - ball->getMaskH() && ball->getVsp() < 0.f) ball->setVsp(ball->getSpeed());
                // If the Ball is above the object, bounce upwards
                else if (ball->getY() < (m_y + ball->getMaskH()) && ball->getVsp() > 0.f) ball->setVsp(-ball->getSpeed());
                else ball->setHsp(-ball->getHsp()); // If the ball is on the side then rebound by reversing the horizontal speed

                m_scene->getGameSystem().m_currentScore += 50; // Adds 50 points to player score
                m_scene->GSMplaySound("bounce_brick"); // Play sound bounce on brick
                m_destroy = true; // This line allows to definitively destroy the object of the scene
            }
        }
        updateCollisionMask();
        updateSprite();
    }

private:
    is::GameDisplay *m_scene;
};

#endif // BRICK_H_INCLUDED
