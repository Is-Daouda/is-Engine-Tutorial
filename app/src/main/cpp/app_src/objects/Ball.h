#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include "../../isEngine/system/display/GameDisplay.h" // This header allows access to the class that manages the scenes,
                                                       // it also integrates the one of the objects of the game
class Ball : public is::MainObject
{
public:
    Ball(float x, float y, is::GameDisplay *scene):
        // We call the constructor of the parent class in order to initialize the object and pass the parameters of the constructor
        MainObject(x, y),
        m_scene(scene)
    {
        // We give the object a name, which will allow us to identify it later
        m_strName = "Ball";

        // We define the sprite of the object with the data entered in the constructor.
        // The "ball" texture will be obtained from the scene in which the object is used
        is::createSprite(scene->GRMgetTexture("ball"), m_sprParent, sf::Vector2f(m_x, m_y), sf::Vector2f(0.f, 0.f));

        // We define the size of the collision mask. Here it equals the size of the sprite of the ball
        setRectangleMask(getTextureWidth(), getTextureHeight());

        // We define the speed of the ball. The more we advance in the game the more the speed increases
        m_speed = 2.f + m_scene->getGameSystem().m_currentLevel;
    }

	// We overload the method which allows to define the mechanisms of the object (i.e. which updates it)
    void step(float const &DELTA_TIME)
    {
        // When we click on the screen throw the ball up
        if (m_scene->getGameSystem().isPressed() && static_cast<int>(m_vsp) == 0) // static_cast <int> (m_vsp) == 0 allows to avoid the repetition of this action
        {
            m_vsp = -m_speed; // we apply the speed to the variable which represents the vertical speed
            m_hsp += is::choose(2, -1.f, 1.f); // here we apply a random speed to the variable which represents the horizontal speed (this makes the game dynamic)
        }

        // This allows the ball not to go out of the playing field
        if ((m_x < 32.f && m_hsp < 0.f) || (m_x + m_w > m_scene->getSceneWidth() - 32.f && m_hsp > 0.f))
        {
            // bump
            m_scene->GSMplaySound("bounce_brick"); // We play a rebound sound in case it hits the edge
            m_hsp = -m_hsp; // We return the ball (rebound effect)
        }

        // Avoid that the Ball comes out at the top of the playing field
        if (m_y < 32.f && m_vsp < 0.f)
        {
            m_vsp = -m_vsp;
            m_scene->GSMplaySound("bounce_brick");
        }

        // If the Ball comes out at the bottom of the scene (The player missed it)
        if (m_y > m_scene->getSceneHeight())
        {
            if (m_scene->getGameSystem().m_currentLives > 1) // If the number of lives is greater than one, the player can resume the game.
            {
                m_scene->getGameSystem().m_currentLives--; // We take a life away

                // This following line allows to return the Paddle to its starting position (position it had when the scene started)
                if (auto paddle = m_scene->SDMgetObject("Paddle"); paddle != nullptr)
                {
                    paddle->setPosition(paddle->getXStart(), paddle->getYStart()); // We change the position
                }

                // We reset the horizontal and vertical speeds of the ball to zero in order to relaunch it again
                m_vsp = 0.f;
                m_hsp = 0.f;

                // This following line allows to return the Ball to its starting position (position it had when the scene started)
                setPosition(m_xStart, m_yStart);

                m_scene->GSMplaySound("lose"); // We play the "lost" sound
            }
            // If the player does not have enough life (go to Game Over Scene)
            else m_scene->quitScene(is::DisplayOption::GAME_OVER); // This line allows you to leave the current scene and go to the one that is entered
        }

        // We check if all the Bricks of the level have been destroyed
        if (m_scene->SDMgetObject("Brick") == nullptr) // This function returns "nullptr" when is::Engine does not find any object of its name
        {
            m_scene->getGameSystem().m_currentLevel++; // We increment the variable which represents the value of the current level
            m_scene->quitScene(is::DisplayOption::GAME_LEVEL); // We relaunch the same scene BUT this time the number of levels to change
        }

        // We apply the speeds to the variables that move the object
        m_x += m_hsp * is::VALUE_CONVERSION * DELTA_TIME; // We apply the horizontal speed to the variable that moves the object on the X axis
        m_y += m_vsp * is::VALUE_CONVERSION * DELTA_TIME; // We apply the vertical speed to the variable that moves the object on the Y axis

        updateSprite(); // This allows to update the sprite of the object (m_sprParent) with all the variables of the object
        updateCollisionMask(); // We update the collision mask (position, size)
    }

private:
    // This variable (of pointer type) allows us to obtain the scene in which the object is located
    is::GameDisplay *m_scene;
};

#endif // BALL_H_INCLUDED
