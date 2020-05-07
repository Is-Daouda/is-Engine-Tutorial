#ifndef HUD_H_INCLUDED
#define HUD_H_INCLUDED

#include "../../../isEngine/system/entity/MainObject.h"
#include "../../../isEngine/system/function/GameTime.h"
#include "../../gamesystem_ext/GameSystemExtended.h"
#include "Player.h"

class HUD : public is::MainObject
{
public:
    HUD(is::GameDisplay &scene, is::GameTime &gameTime, Player &player);
    void loadResources(sf::Font const &fnt);
    void step(float const &DELTA_TIME);
    void draw(sf::RenderTexture &surface);
    void setScore(int val);

private:
    is::GameDisplay &m_scene;
    is::GameTime &m_gameTime;
    Player &m_player;
    sf::Text m_txtHealth, m_txtBonus, m_txtLevelTime, m_txtScore;
};

#endif // HUD_H_INCLUDED
