#include "GameLevel.h"

void GameLevel::gamePlay()
{
    // GAME CONTROLLER
    if (!m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;
    m_gameKey.step(DELTA_TIME);

    // LEVEL CHRONOMETER
    if (m_gameTime.getTimeValue() != 0) m_gameTime.step(DELTA_TIME, is::VALUE_CONVERSION, is::VALUE_TIME); else playerLose();

    // We create a second counter which creates objects randomly
    m_timeCreateOstacle -= is::getMSecond(DELTA_TIME);
    if (m_timeCreateOstacle == 0)
    {
        m_obstacleList.push_back(std::shared_ptr<Obstacle>(new Obstacle(m_texObstacle, m_viewW + 10.f, m_player.getY())));
        m_timeCreateOstacle = 59 * is::choose(3, 10, 3, 5);
    }
    m_timeCreateBonus -= is::getMSecond(DELTA_TIME);
    if (m_timeCreateBonus == 0)
    {
        m_bonusList.push_back(std::shared_ptr<Bonus>(new Bonus(m_texBonus, m_viewW + 10.f, m_player.getY())));
        m_timeCreateBonus = 59 * is::choose(3, 10, 20, 25);
    }

    // OBSTACLE
    updateObjObstacleList();

    // BONUS
    updateObjBonusList();

    // PLAYER
    updateObjPlayer();

    // HUD
    m_gameHud.step(DELTA_TIME);

    // BACKGROUND
    updateBackground();
}
