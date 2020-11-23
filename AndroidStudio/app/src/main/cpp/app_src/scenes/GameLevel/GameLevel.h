#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <memory>
#include "../../../isEngine/system/display/GameDisplay.h"
#include "../../../isEngine/system/function/GameKeyData.h"
#include "../../objects/gamelevel/Player.h"
#include "../../objects/gamelevel/Obstacle.h"
#include "../../objects/gamelevel/HUD.h"
#include "../../objects/gamelevel/Bonus.h"
#include "../../objects/widgets/GameDialog.h"
#include "../../language/GameLanguage.h"

class GameLevel : public is::GameDisplay
{
public:
    GameLevel(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt);
    void step();
    void draw();
    bool loadResources();

private:
    void gamePlay();
    void updateObjObstacleList();
    void updateObjBonusList();
    void playerLose();
    void updateObjPlayer();
    void updateBackground();

private:
    std::vector<std::shared_ptr<Obstacle>> m_obstacleList;
    std::vector<std::shared_ptr<Bonus>> m_bonusList;
    sf::Texture m_texButtonClose, m_texPlayer, m_texObstacle, m_texBonus, m_texDialog, m_texJoystick, m_texLevelBg;
    sf::Sprite m_sprLevelBg, m_sprButtonClose;
    sf::Text m_txtGameInfo;
    sf::SoundBuffer m_sbHurt, m_sbLose, m_sbHaveBonus;
    sf::Sound m_sndHurt, m_sndLose, m_sndHaveBonus;
    sf::Music m_mscLevel;
    GameKeyData m_gameKey;
    is::GameTime m_gameTime;
    GameDialog m_gameDialog;
    Player m_player;
    HUD m_gameHud;
    int m_timeCreateOstacle, m_timeCreateBonus;
};

#endif // GAMELEVEL_H
