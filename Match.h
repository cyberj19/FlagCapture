#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Controller.h"
#include "State.h"
#include "enums.h"
#include "GameSettings.h"
#include "Menu.h"

class State;
class Controller;
class Graphics;

class Match{
	int delay;
	GameSettings _settings;
	MatchStage stage;
	Graphics *graphics;
	Controller *controller;
	State *state;
	SubMenuOptions lastSubMenuChoice;
	Menu subMenu;

	void handleStart();
	void initDraw();
	void handleRunning();
	void handleSubMenu();
	MatchOutput handleEndGame();
	void saveRecord();
	void buildSubMenu();
public:	
	Match(GameSettings settings); // const char* keyboardLayoutA, const char* keyboardLayoutB);
	MatchOutput Play();
};