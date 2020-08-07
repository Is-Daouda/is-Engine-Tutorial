#ifndef GAMEMENU_H_INCLUDED
#define GAMEMENU_H_INCLUDED

#include "../../../isEngine/system/function/GameFunction.h"
#include "../../../isEngine/system/display/GameDisplay.h"

class GameMenu : public is::GameDisplay
{
public:
    GameMenu(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt);
    void step();
    void componentsController();
    void draw();
    bool loadResources();

private:
    sf::Font m_fontTitle;
    sf::Texture m_texPad, m_texScreenBG;
    sf::Sprite m_sprPad1, m_sprPad2, m_sprScreenBG;
    sf::Text m_txtGameTitle, m_txtStartGame, m_txtQuit;
    bool m_isStart, m_closeApplication;
};

#endif // GAMEMENU_H_INCLUDED
