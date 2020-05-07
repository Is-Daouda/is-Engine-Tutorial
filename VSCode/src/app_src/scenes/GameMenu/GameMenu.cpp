#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow &window, sf::View &view, sf::RenderTexture &surface, GameSystemExtended &gameSysExt):
    GameDisplay(window, view, surface, gameSysExt, sf::Color::White),
    m_isStart(true),
    m_closeApplication(false)
{}

void GameMenu::step()
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

    // starting mechanism
    if (m_isStart)
    {
        // window has focus
        if (m_windowIsActive)
        {
            if (!m_showMsg)
            {
                componentsController();
            }
//////////////////////////////////////////////////////////////////////////////////////////////////////
//                                      MESSAGE BOX
//////////////////////////////////////////////////////////////////////////////////////////////////////
            else
            {
                updateMsgBox(DELTA_TIME);

                // when user closes message box in update function execute this instruction
                // "m_waitTime" allow to disable clicks on objects during a moment when user closes message box
                if (!m_showMsg)
                {
                    if (m_closeApplication) // quit game
                    {
                        if (m_msgAnswer == MsgAnswer::YES)
                        {
                            m_window.close();
                            m_isRunning = false;
                        }
                        else
                        {
                            m_waitTime = 20;
                            m_closeApplication = false;
                        }
                    }
                }
            }
        }
    }

    if (m_isClose)
    {
        m_isStart = false;
        m_isRunning = false;
    }
}

void GameMenu::componentsController()
{
    const short OP_START_GAME(0), OP_QUIT(1);

    // allow to know is mouse is in collision with sprite
    bool mouseInCollisonPad(false);

    // allows activated use of buttons
    if (!m_gameSysExt.keyIsPressed(is::GameConfig::KEY_UP) &&
        !m_gameSysExt.keyIsPressed(is::GameConfig::KEY_DOWN) &&
        !m_gameSysExt.isPressed())
            m_gameSysExt.m_keyIsPressed = false;

    // m_isClose allow to deactivate scene object
    if (!m_isClose)
    {
        if (mouseCollision(m_sprPad1) || mouseCollision(m_sprPad2)) mouseInCollisonPad = true;

        // change option with mouse (touch on Android)
        if (mouseCollision(m_sprPad1) && m_optionIndex != OP_START_GAME)  setOptionIndex(OP_START_GAME, true, 1.4f);
        if (mouseCollision(m_sprPad2) && m_optionIndex != OP_QUIT)    setOptionIndex(OP_QUIT, true, 1.4f);

        // avoid the long pressing button effect
        if (!mouseInCollisonPad && m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE))
            m_gameSysExt.m_keyIsPressed = true;

        // change option with keyboard (only for PC)
        if (!m_gameSysExt.m_keyIsPressed && !mouseInCollisonPad)
        {
            if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_UP)) setOptionIndex(-1, false, 1.4f);
            else if (m_gameSysExt.keyIsPressed(is::GameConfig::KEY_DOWN)) setOptionIndex(1, false, 1.4f);
            if (m_optionIndex < OP_START_GAME) m_optionIndex = OP_QUIT;
            if (m_optionIndex > OP_QUIT) m_optionIndex = OP_START_GAME;
        }

        // launch a dialog box which allow to quit the game
        auto lauchDialogBox = [this]()
        {
            showMessageBox(is::lang::msg_quit_game[m_gameSysExt.m_gameLanguage]);
            m_closeApplication = true;
            m_keyBackPressed = false;
        };

        // validate menu option
        if ((m_gameSysExt.isPressed(is::GameSystem::ValidationButton::KEYBOARD) ||
            (m_gameSysExt.isPressed(is::GameSystem::ValidationButton::MOUSE) && mouseInCollisonPad)) &&
            (m_waitTime == 0 && !m_gameSysExt.m_keyIsPressed))
        {
            auto playSelectSnd = [this]()
            {
                m_gameSysExt.playSound(m_sndSelectOption);
                m_sprButtonSelectScale = 1.4f;
                m_gameSysExt.useVibrate(m_vibrateTimeDuration);
            };

            switch (m_optionIndex)
            {
            case OP_START_GAME:
                playSelectSnd();
                m_gameSysExt.m_launchOption = is::DisplayOption::GAME_LEVEL;
                m_isClose = true;
            break;

            case OP_QUIT: lauchDialogBox(); break;
            }
            m_keyBackPressed = false;
        }

        // Quit game
        if (m_keyBackPressed) lauchDialogBox();

        // change the color of the texts according to the chosen option
        setTextAnimation(m_txtStartGame, m_sprPad1, OP_START_GAME);
        setTextAnimation(m_txtQuit,  m_sprPad2, OP_QUIT);

        // PAD animation
        is::scaleAnimation(DELTA_TIME, m_sprButtonSelectScale, m_sprButtonSelect, is::getSFMLObjXScale(m_sprPad1));
    }
}

void GameMenu::draw()
{
    const short OP_START_GAME(0),
                OP_QUIT(1);

    // draw background
    m_surface.draw(m_sprScreenBG);

    // draw game title
    m_surface.draw(m_txtGameTitle);

    // draw button
    if (m_optionIndex != OP_START_GAME) m_surface.draw(m_sprPad1);
    if (m_optionIndex != OP_QUIT) m_surface.draw(m_sprPad2);
    m_surface.draw(m_sprButtonSelect);
    m_surface.draw(m_txtStartGame);
    m_surface.draw(m_txtQuit);

    // message box
    drawMsgBox();
}
