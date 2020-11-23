#include "GameLevel.h"

/*
 * This file contains the implementation of the functions which update game play
 * objects (view, enemy, bonus, ..)
*/

void GameLevel::updateObjObstacleList()
{
    WITH(m_obstacleList.size())
    {
        if (is::instanceExist(m_obstacleList[_I]))
        {
            // apply player acceleration on the object
            m_obstacleList[_I]->moveX(-m_player.getSpeed() * DELTA_TIME);

            // If the player touches the obstacle, his health is removed. if he is no longer healthy then game over
            if (m_player.placeMetting(0, 0, m_obstacleList[_I]))
            {
                if (m_player.getHealth() > 1)
                {
                    m_gameSysExt.playSound(m_sndHurt);
                    m_player.setIsHurt(30.f); // make blink
                    m_player.addHealth(-1);
                    m_obstacleList[_I].reset();
                    break;
                }
                else playerLose();
            }
            m_obstacleList[_I]->step(DELTA_TIME); // update object

            // We destroy the object when it leaves to the left of the view
            if (m_obstacleList[_I]->getX() < -32.f)
            {
                m_gameSysExt.m_currentScore += m_obstacleList[_I]->getScorePoint(); // add score point
                m_obstacleList[_I].reset();
            }
        }
    }
}

void GameLevel::updateObjBonusList()
{
    WITH(m_bonusList.size())
    {
        if (is::instanceExist(m_bonusList[_I]))
        {
            // apply player acceleration on the object
            m_bonusList[_I]->moveX(-m_player.getSpeed() * DELTA_TIME);

            if (m_player.placeMetting(0, 0, m_bonusList[_I]) && m_bonusList[_I]->getStep() == 0)
            {
                m_gameSysExt.m_currentBonus++;
                m_gameTime.addTimeValue(0, 15, 0); // add 10 second
                m_gameSysExt.m_currentScore += m_bonusList[_I]->getScorePoint(); // add score point
                m_gameSysExt.playSound(m_sndHaveBonus);
                m_bonusList[_I]->addStep();
            }
            m_bonusList[_I]->step(DELTA_TIME); // update object

            // destruction
            if (m_bonusList[_I]->isDestroyed() || m_bonusList[_I]->getX() < -32.f) m_bonusList[_I].reset();
        }
    }
}

void GameLevel::playerLose()
{
    m_mscLevel.stop();
    m_gameSysExt.playSound(m_sndLose);
    m_txtGameInfo.setString(is::lang::msg_game_over[m_gameSysExt.m_gameLanguage] +
                            is::numToStr(m_gameSysExt.m_currentScore) + "\n" +
                            is::lang::msg_clic_restart[m_gameSysExt.m_gameLanguage]);
    m_player.setIsActive(false);
}

void GameLevel::updateObjPlayer()
{
    m_player.step(DELTA_TIME);
}

void GameLevel::updateBackground()
{
    // Allows you to repeat the background endlessly
    if (is::getSFMLObjX(m_sprLevelBg) < -static_cast<float>(m_texLevelBg.getSize().x)) is::setSFMLObjX(m_sprLevelBg, 0.f);
    is::moveSFMLObjX(m_sprLevelBg, -(1.f * is::VALUE_CONVERSION + m_player.getSpeed()) * DELTA_TIME);
}
