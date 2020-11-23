#include "GameLevel.h"

bool GameLevel::loadResources()
{
    if (!GameDisplay::loadParentResources()) return false;

    // load buffers
    if (!m_sbHurt.loadFromFile(is::GameConfig::SFX_DIR + "hurt.ogg"))            return false;
    if (!m_sbLose.loadFromFile(is::GameConfig::SFX_DIR + "lose.ogg"))            return false;
    if (!m_sbHaveBonus.loadFromFile(is::GameConfig::SFX_DIR + "have_bonus.ogg")) return false;

    // sound
    m_sndHurt.setBuffer(m_sbHurt);
    m_sndLose.setBuffer(m_sbLose);
    m_sndHaveBonus.setBuffer(m_sbHaveBonus);

    // GUI resources
    if (!m_texButtonClose.loadFromFile(is::GameConfig::GUI_DIR + "button_close.png")) return false;
    if (!m_texDialog.loadFromFile(is::GameConfig::GUI_DIR + "dialog_box.png"))      return false;
    if (!m_texJoystick.loadFromFile(is::GameConfig::GUI_DIR + "game_pad.png")) return false;
    m_gameKey.loadResources(m_texJoystick);
    m_gameKey.step(0.f);

    // sprites
    if (!m_texPlayer.loadFromFile(is::GameConfig::SPRITES_DIR + "player.png"))  return false;
    if (!m_texBonus.loadFromFile(is::GameConfig::SPRITES_DIR + "bonus.png"))    return false;
    if (!m_texObstacle.loadFromFile(is::GameConfig::SPRITES_DIR + "obstacle.png")) return false;

    // background
    if (!m_texLevelBg.loadFromFile(is::GameConfig::TILES_DIR + "level_bg.png"))   return false;

    // CREATION OF THE LEVEL
    // place the player
    m_player.setPosition(32.f, 220.f);
    m_player.loadResources(m_texPlayer);

    // set time
    m_gameTime.setTimeValue(0, 29, 59);

    // create game over text
    is::createText(m_fontMsg, m_txtGameInfo, "", 240.f, 200.f, false, 24);

    // create close button
    is::createSprite(m_texButtonClose, m_sprButtonClose, sf::IntRect(0, 0, 32, 32), sf::Vector2f(600.f, 16.f), sf::Vector2f(0.f, 0.f), true);

    // build background
    // We enlarge the size of the background to make it repeat in game endlessly
    is::createSprite(m_texLevelBg, m_sprLevelBg, sf::IntRect(0, 0, m_texLevelBg.getSize().x * 2.5, 480), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), true);

    // load HUD resources
    m_gameHud.setPosition(m_viewX, m_viewY);
    m_gameHud.loadResources(m_fontSystem);

    // load Dialog Box resources
    m_gameDialog.loadResources(m_texDialog, m_fontSystem);
    m_gameDialog.setDialog(GameDialog::DialogIndex::DIALOG_PLAYER_MOVE);

    // load level music
    m_mscLevel.openFromFile(is::GameConfig::MUSIC_DIR + "world_1_music.ogg");
    m_mscLevel.setLoop(true);
    m_mscLevel.play();

    return true;
}
