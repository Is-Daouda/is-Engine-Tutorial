#ifndef GAMEOVER_H_INCLUDED
#define GAMEOVER_H_INCLUDED

// We include the Game Over Controller header
#include "../../objects/GameOverController.h"

class GameOver : public is::GameDisplay
{
public:
    /*  					/!\ WARNING! /!\
     * This constructor is no longer supported in this version of the engine. Use the one below.
     *
     * GameOver(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
     *   GameDisplay(window, view, surface, gameSysExt, sf::Color::Black) {}
     */

    GameOver(is::GameSystemExtended &gameSysExt):
        GameDisplay(gameSysExt, sf::Color::Black /* => scene color*/) {}

    void loadResources()
    {
        // load font and texture
        GameDisplay::loadParentResources(); // allows to load system resource (very important never forgot to call him)

        // Added the Game Over Controller object to the scene that displays the Game Over text
        SDMaddSceneObject(std::make_shared<GameOverController>(this)); // It also allows to change the scene after 3 seconds

        GSMaddSound("game_over", is::GameConfig::SFX_DIR + "game_over.wav"); // Add music
        GSMplaySound("game_over"); // Play music when the scene starts
    }
};

#endif // GAMEOVER_H_INCLUDED
