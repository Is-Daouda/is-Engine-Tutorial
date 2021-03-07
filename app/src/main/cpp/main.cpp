#if defined(IS_ENGINE_VS_CODE)
#include "Main.hpp"
#endif
#if defined(IS_ENGINE_HTML_5)
#include <emscripten.h>
#include <emscripten/bind.h>

inline std::vector<std::string> *vectorFromIntPointer(uintptr_t vec) {
  return reinterpret_cast<std::vector<std::string> *>(vec);
}
EMSCRIPTEN_BINDINGS(Wrappers) {
  emscripten::register_vector<std::string>("VectorString").constructor(&vectorFromIntPointer, emscripten::allow_raw_pointers());
};
#endif
#include "isEngine/core/GameEngine.h"

////////////////////////////////////////////////////////////
/// \brief application entry point
////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
#if defined(IS_ENGINE_VS_CODE)
#if defined(_DEBUG)
	// Display a text in the console to inform that we are in Debug mode on Visual Studio Code
	is::showLog("Debug Mode Start!");
#endif
#endif
    is::GameEngine game;
#if defined(IS_ENGINE_VS_CODE)
#ifdef SFML_SYSTEM_WINDOWS
	// Allows to create the icon for the application when developing with Visual Studio Code
	windowsHelper.setIcon(game.getRenderWindow().getSystemHandle());
#endif
#endif

#if defined(IS_ENGINE_USE_MAIN_LOOP)
    game.play();
#else
    game.basicSFMLmain();
#endif // defined

    #if defined (__ANDROID__)
    std::terminate(); // close application
    #else
    return 0;
    #endif // defined
}
