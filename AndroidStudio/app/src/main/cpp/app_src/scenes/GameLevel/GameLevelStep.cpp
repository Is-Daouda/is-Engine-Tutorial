#include "GameLevel.h"

void GameLevel::step()
{
    DELTA_TIME = getDeltaTime();
    updateTimeWait(DELTA_TIME);

    // even loop
    while (m_window.pollEvent(m_event))
    {
        controlEventFocusClosing();
        if (m_event.type == sf::Event::KeyReleased)
        {
            if (m_event.key.code == is::GameConfig::KEY_CANCEL) m_keyBackPressed = true;
        }
    }

    // if the window is activated launch the game
    if (m_windowIsActive)
    {
        // If the player loses and clicks on the screen then restart the level
        if (m_gameSysExt.isPressed() && !m_player.getIsActive())
        {
            m_gameSysExt.playSound(m_sndSelectOption);
            m_gameSysExt.m_launchOption = is::DisplayOption::RESTART_LEVEL;
            m_isRunning = false;
        }

        // if player clicks on close button sprite then quit game
        if (mouseCollision(m_sprButtonClose) && m_gameSysExt.isPressed())
        {
            m_mscLevel.stop();
            m_gameSysExt.playSound(m_sndSelectOption);
            m_gameSysExt.m_launchOption = is::DisplayOption::MAIN_MENU;
            m_isRunning = false;
        }
        if (!m_gameDialog.showDialog())
        {
            if (m_player.getIsActive()) gamePlay();
        }
        else
        {
            if (!m_gameSysExt.keyIsPressed(is::GameConfig::KEY_A) && !m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = false;
            if (!mouseCollision(m_gameDialog.getSprite()) && m_gameSysExt.isPressed()) m_gameSysExt.m_keyIsPressed = true;
            m_gameDialog.setPosition(m_viewX, m_viewY + 32.f);
        }
        m_gameDialog.step(DELTA_TIME);
    }
}
