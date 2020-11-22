QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Confirm that we are using Qt IDE with the engine
DEFINES += IS_ENGINE_QT

# Game source files
HEADERS += \
    ../../cpp/app_src/activity/GameActivity.h \
    ../../cpp/app_src/activity/SwooshFiles.h \
    ../../cpp/app_src/config/ExtraConfig.h \
    ../../cpp/app_src/config/GameConfig.h \
    ../../cpp/app_src/gamesystem_ext/GameSystemExtended.h \
    ../../cpp/app_src/language/GameLanguage.h \
    ../../cpp/app_src/objects/HelloWorld.h \
    ../../cpp/app_src/objects/widgets/GameDialog.h \
    ../../cpp/app_src/scenes/HelloScene/HelloScene.h

SOURCES += \
        ../../cpp/app_src/gamesystem_ext/GameSystemExtended.cpp \
        ../../cpp/app_src/objects/widgets/GameDialog.cpp \
        ../../cpp/basicSFMLmain.cpp

# is::Engine source files
HEADERS += \
    ../../cpp/isEngine/core/ActivityController.h \
    ../../cpp/isEngine/core/GameEngine.h \
    ../../cpp/isEngine/system/android/AdmobManager.h \
    ../../cpp/isEngine/system/display/GameDisplay.h \
    ../../cpp/isEngine/system/display/SDM.h \
    ../../cpp/isEngine/system/entity/Background.h \
    ../../cpp/isEngine/system/entity/Button.h \
    ../../cpp/isEngine/system/entity/Form.h \
    ../../cpp/isEngine/system/entity/MainObject.h \
    ../../cpp/isEngine/system/entity/parents/DepthObject.h \
    ../../cpp/isEngine/system/entity/parents/Destructible.h \
    ../../cpp/isEngine/system/entity/parents/FilePath.h \
    ../../cpp/isEngine/system/entity/parents/Health.h \
    ../../cpp/isEngine/system/entity/parents/HurtEffect.h \
    ../../cpp/isEngine/system/entity/parents/Name.h \
    ../../cpp/isEngine/system/entity/parents/ScorePoint.h \
    ../../cpp/isEngine/system/entity/parents/Step.h \
    ../../cpp/isEngine/system/entity/parents/Type.h \
    ../../cpp/isEngine/system/entity/parents/Visibilty.h \
    ../../cpp/isEngine/system/function/GameFunction.h \
    ../../cpp/isEngine/system/function/GameKeyData.h \
    ../../cpp/isEngine/system/function/GameKeyName.h \
    ../../cpp/isEngine/system/function/GameSlider.h \
    ../../cpp/isEngine/system/function/GameSystem.h \
    ../../cpp/isEngine/system/function/GameTime.h \
    ../../cpp/isEngine/system/graphic/GRM.h \
    ../../cpp/isEngine/system/graphic/GameFont.h \
    ../../cpp/isEngine/system/graphic/GameTexture.h \
    ../../cpp/isEngine/system/graphic/TransitionEffect.h \
    ../../cpp/isEngine/system/isEngineWrapper.h \
    ../../cpp/isEngine/system/sound/GSM.h \
    ../../cpp/isEngine/system/sound/GameMusic.h \
    ../../cpp/isEngine/system/sound/GameSound.h

SOURCES += \
        ../../cpp/isEngine/core/GameEngine.cpp \
        ../../cpp/isEngine/system/display/GameDisplay.cpp \
        ../../cpp/isEngine/system/entity/MainObject.cpp \
        ../../cpp/isEngine/system/function/GameFunction.cpp \
        ../../cpp/isEngine/system/function/GameKeyData.cpp \
        ../../cpp/isEngine/system/function/GameSlider.cpp \
        ../../cpp/isEngine/system/function/GameSystem.cpp \
        ../../cpp/isEngine/system/function/GameTime.cpp \
        ../../cpp/isEngine/system/graphic/TransitionEffect.cpp \
        ../../cpp/isEngine/system/isEngineWrapper.cpp \
        ../../cpp/main.cpp

LIBS += -LC:\SFML_Qt_MinGW_\lib\

CONFIG(debug, debug|release): LIBS += -lsfml-audio-d \
                                    -lsfml-network-d \
                                    -lsfml-graphics-d \
                                    -lsfml-window-d \
                                    -lsfml-system-d \
                                    -lsfml-main-d

CONFIG(release, debug|release): LIBS += -lsfml-audio \
                                    -lsfml-network \
                                    -lsfml-graphics \
                                    -lsfml-window \
                                    -lsfml-system \
                                    -lsfml-main

INCLUDEPATH += C:\SFML_Qt_MinGW_\include
DEPENDPATH += C:\SFML_Qt_MinGW_\include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
