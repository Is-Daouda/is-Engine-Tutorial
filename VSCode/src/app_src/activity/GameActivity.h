#ifndef GAMEACTIVITY_H_INCLUDED
#define GAMEACTIVITY_H_INCLUDED

#include <memory>

#include "SwooshFiles.h"
#include "../scenes/GameMenu/GameMenu.h"
#include "../scenes/GameLevel/GameLevel.h"

using namespace swoosh::intent;

////////////////////////////////////////////////////////////
/// Allows to manage the different scenes of the game and
/// to interconnect the engine and the Swoosh library to make
/// transition effects
////////////////////////////////////////////////////////////
class GameActivity : public Activity
{
private:
    std::shared_ptr<is::GameDisplay> m_gameScene;

public:
    GameActivity(ActivityController& controller, GameSystemExtended &gameSysExt) :
        Activity(&controller)
    {
        m_gameScene = nullptr;
        switch (gameSysExt.m_launchOption)
        {
        case is::DisplayOption::MAIN_MENU:
            m_gameScene = std::shared_ptr<is::GameDisplay>(new GameMenu(controller.getWindow(),
                                                                        getView(),
                                                                        *(this->controller->getSurface()),
                                                                        gameSysExt));
        break;
        case is::DisplayOption::GAME_LEVEL:
			m_gameScene = std::shared_ptr<is::GameDisplay>(new GameLevel(controller.getWindow(),
                                                                         getView(),
                                                                         *(this->controller->getSurface()),
                                                                         gameSysExt));
        break;
        default:
			is::showLog("Error : Scene not found !");
			std::terminate();
		break;
        }
        if (!m_gameScene->loadResources())
		{
			is::showLog("Error in loadResources function !");
			std::terminate();
		}

        this->setBGColor(m_gameScene->getBgColor());
    }
    virtual void onUpdate(double elapsed)
    {
        if (m_gameScene->isRunning()) m_gameScene->step();
        else
        {
            switch (m_gameScene->getGameSystem().m_launchOption)
            {
                case is::DisplayOption::MAIN_MENU:
                    {
                        using transition = segue<VerticalSlice, sec<2>>;
                        using action = transition::to<GameActivity>;
                        getController().replace<action>(m_gameScene->getGameSystem());
                    }
                break;

                case is::DisplayOption::GAME_LEVEL:
                    {
                        using transition = segue<VerticalSlice, sec<2>>;
                        using action = transition::to<GameActivity>;
                        getController().replace<action>(m_gameScene->getGameSystem());
                    }
                break;

                case is::DisplayOption::RESTART_LEVEL : // restart level (when player loses)
                    m_gameScene->getGameSystem().initData(false);
                    m_gameScene->getGameSystem().m_launchOption = is::DisplayOption::GAME_LEVEL;

                    using transition = segue<BlackWashFade>;
                    using action = transition::to<GameActivity>;
                    getController().replace<action>(m_gameScene->getGameSystem());
                break;

                default:
                    is::showLog("Error : Scene not found !");
                    std::terminate();
                break;
            }
        }
    }
    virtual void onDraw(sf::RenderTexture& surface)
    {
        m_gameScene->drawScreen();
    }
    virtual void onStart() {}
    virtual void onLeave(){}
    virtual void onExit(){}
    virtual void onEnter(){}
    virtual void onResume(){}
    virtual void onEnd() {}
};

#endif // GAMEACTIVITY_H_INCLUDED
