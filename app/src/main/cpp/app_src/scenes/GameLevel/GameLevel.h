#ifndef GAMELEVEL_H_INCLUDED
#define GAMELEVEL_H_INCLUDED

// We include the header of the objects we are going to use in the scene
#include "../../objects/Brick.h"
#include "../../objects/Ball.h"
#include "../../objects/HUD.h"
#include "../../objects/Paddle.h"

class GameLevel : public is::GameDisplay
{
public:
    GameLevel(sf::RenderWindow &window, sf::View &view, is::Render &surface, is::GameSystemExtended &gameSysExt):
        GameDisplay(window, view, surface, gameSysExt, sf::Color::Black /* => scene color*/) {}

    void loadResources() {
        // load font and texture
        GameDisplay::loadParentResources();
        GRMaddTexture("ball", is::GameConfig::SPRITES_DIR + "ball.png");
        GRMaddTexture("paddle", is::GameConfig::SPRITES_DIR + "paddle.png");
        GRMaddTexture("brick", is::GameConfig::SPRITES_DIR + "brick.png");
        auto &bgTex = GRMaddTexture("level_background", is::GameConfig::SPRITES_DIR + "level_background.png");

        // Add the background that represents the playing field to the position x = 0 and y = 0 (in the upper left corner of the scene)
        // Do not center the background image
        // It takes the value of depth one (1) so that it appears below the other objects of the scene
        SDMaddSprite(bgTex, "level_background", 0.f, 0.f, false, 1);

        m_sceneWidth = is::getSFMLTextureWidth(bgTex); // The size of the scene (game fields). It is defined according to the size of the Background

        // Adding bricks to the scene
        // The more the number of levels increases, the more the number of row of bricks increases
        for (int i(0); i < 14; i++) // columns
        {
            for (int j(0); j < 4 + getGameSystem().m_currentLevel /* increases according to the number of levels reached*/; j++) // rows
            {
                SDMaddSceneObject(std::make_shared<Brick>(i * 32.f + 32.f, j * 32.f + 32.f, this)); // Adding bricks
            }
        }

        // Adding Paddle to the scene
        auto objPaddle = std::make_shared<Paddle>(m_sceneWidth / 2.f - 32.f, m_sceneHeight - 96.f, this);
        SDMaddSceneObject(objPaddle);

        // Add the Ball and position it above the Paddle
        SDMaddSceneObject(std::make_shared<Ball>(objPaddle->getX() + 24.f, objPaddle->getY() - 10.f, this));

        // Addition of the HUD object just right of the background
        SDMaddSceneObject(std::make_shared<HUD>(m_sceneWidth, 0.f, this));

        // Adding sounds
        GSMaddSound("lose", is::GameConfig::SFX_DIR + "lose.wav");
        GSMaddSound("bounce_paddle", is::GameConfig::SFX_DIR + "bounce_paddle.wav");
        GSMaddSound("bounce_brick", is::GameConfig::SFX_DIR + "bounce_brick.wav");
        GSMaddSound("level_start", is::GameConfig::SFX_DIR + "level_start.ogg");

        GSMplaySound("level_start"); // Play music when the scene starts
    }
};
#endif // GAMEMENU_H_INCLUDED
