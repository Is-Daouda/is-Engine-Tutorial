#ifndef GAMEOVERCONTROLLER_H_INCLUDED
#define GAMEOVERCONTROLLER_H_INCLUDED

#include "../../isEngine/system/display/GameDisplay.h"

class GameOverController : public is::MainObject
{
public:
    GameOverController(is::GameDisplay *scene):
        MainObject(),
        m_scene(scene)
    {
        // We define the text with the default font of the engine, we also
        // assign the text "Game Over" and the value 32 as character size
        is::createText(m_scene->getFontMsg(), m_txtGameOver, "Game Over", 320.f, 220.f, true, 32);
    }

    void step(float const &DELTA_TIME)
    {
        // We start the millisecond counter
        m_time += is::getMSecond(DELTA_TIME); // This function returns the number of milliseconds that elapse

        // If the counter value exceeds three (3) seconds
        if (m_time > 3.f * is::SECOND)
        {
            m_scene->quitScene(is::DisplayOption::GAME_MENU); // We leave the current scene and launch the Menu scene
        }
    }

    // Overloading the display function to display the Game Over text
    void draw(is::Render &render)
    {
        render.draw(m_txtGameOver);
    }

private:
    is::GameDisplay *m_scene;

    // We declare an SFML text which will display "Game Over" on the screen
    sf::Text m_txtGameOver;
};

#endif // GAMEOVERCONTROLLER_H_INCLUDED
