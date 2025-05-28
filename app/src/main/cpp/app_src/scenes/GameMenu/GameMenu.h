#ifndef GAMEMENU_H_INCLUDED
#define GAMEMENU_H_INCLUDED

// We include the header of the Button that we created
#include "../../objects/GameButton.h"

class GameMenu : public is::GameDisplay
{
public:
    /*  					/!\ WARNING! /!\
     * This constructor is no longer supported in this version of the engine. Use the one below.
     *
     * GameMenu(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
     *   GameDisplay(window, view, surface, gameSysExt, sf::Color::Black) {}
     */

    GameMenu(is::GameSystemExtended &gameSysExt):
        // We call the constructor of the parent class
        GameDisplay(gameSysExt, sf::Color::Black /* => scene color*/) {}

    void loadResources()
    {
        // load font and texture
        GameDisplay::loadParentResources(); // Allows to load system resource (very important never forgot to call him)
        GRMaddTexture("game_title", is::GameConfig::SPRITES_DIR + "game_title.png"); // Load texture for title sprite
        GRMaddTexture("button", is::GameConfig::GUI_DIR + "button.png"); // Load texture for button objects

        // Add the sprite title in the middle of the scene and center the image of the sprite (it is automatically displayed)
        SDMaddSprite(GRMgetTexture("game_title"), "game_title", m_viewW / 2.f, 64.f, true);

        // Addition of the button used to launch the level (with the object name "Start")
        SDMaddSceneObject(std::make_shared<GameButton>(m_viewW / 2.f, m_viewH / 2.f - 32.f, "START GAME", "Start", this));

        // Added button that is used to quit the game (with the object name "Quit")
        SDMaddSceneObject(std::make_shared<GameButton>(m_viewW / 2.f, m_viewH / 2.f + 32.f, "QUIT GAME", "Quit", this));

        GSMaddSound("game_menu", is::GameConfig::SFX_DIR + "game_menu.wav"); // Add music
        GSMplaySound("game_menu"); // Play music when the scene starts
    }
};

#endif // GAMEMENU_H_INCLUDED
