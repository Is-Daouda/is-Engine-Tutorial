# game source file
set(
    app_src
	
	# game system extended
	app_src/gamesystem_ext/GameSystemExtended.cpp

	# game scene
	app_src/scenes/GameLevel/GameLevelConstructor.cpp
	app_src/scenes/GameLevel/GameLevelDraw.cpp
	app_src/scenes/GameLevel/GameLevelLoadResource.cpp
	app_src/scenes/GameLevel/GameLevelStep.cpp
	app_src/scenes/GameLevel/GameLevelStepGamePlay.cpp
	app_src/scenes/GameLevel/GameLevelStepUpdateObj.cpp
	app_src/scenes/GameMenu/GameMenu.cpp
	app_src/scenes/GameMenu/GameMenuLoadResource.cpp

	# game objects
	app_src/objects/gamelevel/Bonus.cpp
	app_src/objects/gamelevel/HUD.cpp
	app_src/objects/gamelevel/Obstacle.cpp
	app_src/objects/gamelevel/Player.cpp

	# widgets
	app_src/objects/widgets/CancelButton.cpp
	app_src/objects/widgets/GameDialog.cpp
	app_src/objects/widgets/PauseOption.cpp
)