#ifndef GAMEBUTTON_H_INCLUDED
#define GAMEBUTTON_H_INCLUDED

// We include the header which will allow us to use the Buttons of is::Engine
#include "../../isEngine/system/entity/Button.h"

class GameButton : public is::Button
{
public:
    GameButton(float x, float y, std::string const &title, std::string const &name, is::GameDisplay *scene):
        // We call the constructor of the parent class
        Button(scene->GRMgetTexture("button"), x, y, title, name, true, scene)
    {}

	// We overload the method that is triggered during a click
    void onClick()
    {
        // This line is used to launch the level scene and to initialize the variables for the gameplay (score, life, level)
        if (m_strName == "Start")
        {
            m_scene->getGameSystem().initData(); // We initialize the game play variables (score, life, level)
            m_scene->quitScene(is::DisplayOption::GAME_LEVEL); // We launch the level scene
        }

        // This line allows you to quit the game
        if (m_strName == "Quit")
        {
            m_scene->quitScene(); // When you leave a scene without starting the next scene, is::Engine stops the game
        }
    }
};

#endif // GAMEBUTTON_H_INCLUDED
