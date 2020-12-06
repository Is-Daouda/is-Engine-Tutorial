#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "../../isEngine/system/display/GameDisplay.h"

class HUD : public is::MainObject
{
public:
    HUD(float x, float y, is::GameDisplay *scene):
        MainObject(x, y),
        m_scene(scene)
    {
        // We define the text with the default font of the engine, we also
        // assign the color red and the value 16 as character size
        is::createText(scene->getFontMsg(), m_txtHUD, "", m_x, m_y, sf::Color::Red, 16);
    }

    void step(float const &DELTA_TIME)
    {
        // Before counting the HI Score, the player's score must exceed this
        if (m_scene->getGameSystem().m_currentScore > m_scene->getGameSystem().m_currentHiScore)
            m_scene->getGameSystem().m_currentHiScore = m_scene->getGameSystem().m_currentScore;

        // We define the text with the data of the GameSystem (object that manages game data)
        m_txtHUD.setString("Score\n" + is::numToStr(m_scene->getGameSystem().m_currentScore) + // player score
                           "\n\n" +
                           "Hi-Score\n" + is::numToStr(m_scene->getGameSystem().m_currentHiScore) + // HI score
                           "\n\n" +
                           "Lives\n" + is::numToStr(m_scene->getGameSystem().m_currentLives) + // the number of lives remaining
                           "\n\n" +
                           "Round\n" + is::numToStr(m_scene->getGameSystem().m_currentLevel + 1) // the level (+1 because the level value starts from zero (0))
                           );
    }

    // Overload display function to display SFML text
    void draw(is::Render &render)
    {
        render.draw(m_txtHUD);
    }

private:
    is::GameDisplay *m_scene;

    // We declare an SFML text which will display the game information on the screen
    sf::Text m_txtHUD;
};

#endif // HUD_H_INCLUDED
