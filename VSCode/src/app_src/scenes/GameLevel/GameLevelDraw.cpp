#include "GameLevel.h"

void GameLevel::draw()
{
    // draw background
    m_surface.draw(m_sprLevelBg);

    // draw bonus
    WITH(m_bonusList.size())
    {
        if (is::instanceExist(m_bonusList[_I]))
        {
            if (m_bonusList[_I]->inViewRec(*this)) m_bonusList[_I]->draw(m_surface);
        }
    }

    // draw blocks
    WITH(m_obstacleList.size())
    {
        if (is::instanceExist(m_obstacleList[_I]))
        {
            if (m_obstacleList[_I]->inViewRec(*this)) m_obstacleList[_I]->draw(m_surface);
        }
    }

    m_player.draw(m_surface);
    m_gameHud.draw(m_surface);

    // draw close button
    m_surface.draw(m_sprButtonClose);
    if (!m_player.getIsActive()) m_surface.draw(m_txtGameInfo);

    m_gameKey.draw(m_surface);

    // draw dialog box
    m_gameDialog.draw(m_surface);
}
