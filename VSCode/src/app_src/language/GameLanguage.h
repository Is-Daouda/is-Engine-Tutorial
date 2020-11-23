#ifndef GAMELANGUAGE_H_INCLUDED
#define GAMELANGUAGE_H_INCLUDED

#include "../../isEngine/system/function/GameKeyName.h"

/*
 * This file allows you to define the languages you want to use in the game.
 * To use a language you must define a array. the first index represents the first language
 * (e.g lang_array[0] => eng) and the index following its translation (e.g lang_array[1] => fr).
 *
 * example to display several sentences in the dialog manager.
 * lang_array[] = {"eng 1", "translation fr 1", "eng 2", "translation fr 2", ...};
 * (Go to the GameDialog Class to see how we implement languages to make sentences in dialogs)
 */
namespace is
{
//////////////////////////////////////////////////////
/// \brief Access to content that allows internationalization of the game
///
//////////////////////////////////////////////////////
namespace lang
{
////////////////////////////////////////////////////////////
/// \brief Represent the index of each language
///
////////////////////////////////////////////////////////////
enum GameLanguage
{
    ENGLISH,  ///< English language index
    FRANCAIS, ///< French language index
};

// ------------------------ message box answer ------------------------
static std::string pad_answer_ok[] = {"OK", "OK"};
static std::string pad_answer_yes[] = {"YES", "OUI"};
static std::string pad_answer_no[]  = {"NO", "NON"};

// ------------------------ intro ------------------------
static std::string pad_game_language[] = {"English", "French"};

// ------------------------ menu ------------------------
static std::string pad_main_menu[] = {"Main Menu", "Menu Principal"};
static std::string pad_new_game[]  = {"Start Game", "Nouvelle Partie"};
static std::string pad_quit_game[] = {"Quit Game", "Quitter le Jeu"};
static std::string msg_quit_game[] = {"Quit game?", "Quitter le jeu?"};

// ------------------------ level dialog ------------------------
static std::string pad_dialog_skip[] = {"Skip", "Passer"};

/*
 * The message changes depending on the operating system.
 * On Android we just display LEFT, UP, RIGHT, DOWN, A, B in the messages
 * as the key to use to control the player.
 * On windows or Linux, the names of the keyboard keys to be used to control
 * the player are displayed because they can change according to the values
 * defined in the GameConfig.cpp file.
 */
#if defined(__ANDROID__)
static std::wstring dialog_player_move[] = {L"Press LEFT, RIGHT, UP or DOWN to move.\n"
                                           "Press A to Accelerate and B to decelerate.",
                                                L"Appuie sur GAUCHE, DROITE, HAUT, BAS pour te déplacer.\n"
                                                "Appuie sur A pour Accélerer et B pour Ralentire."};
#else
static std::wstring dialog_player_move[] = {L"Press " + is::getKeyWName(is::GameConfig::KEY_LEFT) + L", " +
                                                        is::getKeyWName(is::GameConfig::KEY_RIGHT) + L", " +
                                                        is::getKeyWName(is::GameConfig::KEY_UP) + L" or " +
                                                        is::getKeyWName(is::GameConfig::KEY_DOWN) + L" to move.\n"
                                           "Press " + is::getKeyWName(is::GameConfig::KEY_A) + L" to Accelerate and " +
                                                      is::getKeyWName(is::GameConfig::KEY_B) + L" to Decelerate.",
                                                L"Appuie sur " + is::getKeyWName(is::GameConfig::KEY_LEFT) + L", " +
                                                                 is::getKeyWName(is::GameConfig::KEY_RIGHT) + L", " +
                                                                 is::getKeyWName(is::GameConfig::KEY_UP) + L" ou " +
                                                                 is::getKeyWName(is::GameConfig::KEY_DOWN) + L" pour te déplacer.\n"
                                                "Appuie sur " + is::getKeyWName(is::GameConfig::KEY_A) + L" pour Accélerer et " +
                                                                is::getKeyWName(is::GameConfig::KEY_B) + L" pour Ralentire."};
#endif // defined

// ------------------------ game level ------------------------
static std::string msg_game_over[] = {"Your score  : ", "Votre score : "};
static std::string msg_clic_restart[] = {"Click to restart", "Cliquer pour recommencer"};
}
}

#endif // GAMELANGUAGE_H_INCLUDED
