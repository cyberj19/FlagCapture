#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Controller.h"
#include "State.h"
#include "enums.h"

class State;
class Controller;
class Graphics;

class Match{
	MatchStage stage;
	Graphics *graphics;
	Controller *controller;
	State *state;
	SubMenuOptions lastSubMenuChoice;

	void handleStart();
	void initDraw();
	void handleRunning();
	void handleSubMenu();
	MatchOutput handleEndGame() {
		controller->clearBuffer();
		if (lastSubMenuChoice == SubMenuOptions::EXIT_GAME)
			return MatchOutput::QUIT_GAME;
		else if (lastSubMenuChoice == SubMenuOptions::MAIN_MENU)
			return MatchOutput::MATCH_TERMINATED;
		else if (state->winner == Player::A)
			return MatchOutput::WINNER_A;
		else
			return MatchOutput::WINNER_B;
	}
public:	
	Match(const char* keyboardLayoutA, const char* keyboardLayoutB);
	MatchOutput Play();
};