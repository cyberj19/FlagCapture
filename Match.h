#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Controller.h"
#include "State.h"
#include "enums.h"
#include "GameSettings.h"

class State;
class Controller;
class Graphics;

class Match{
	int delay;

	MatchStage stage;
	Graphics *graphics;
	Controller *controller;
	State *state;
	SubMenuOptions lastSubMenuChoice;

	void handleStart();
	void initDraw();
	void handleRunning();
	void handleSubMenu();
	MatchOutput handleEndGame();
public:	
	Match(GameSettings settings); // const char* keyboardLayoutA, const char* keyboardLayoutB);
	MatchOutput Play();
};