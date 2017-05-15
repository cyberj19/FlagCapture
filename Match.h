#pragma once
#include <Windows.h>
#include "enums.h"
#include "GameSettings.h"
#include "Menu.h"

class State;
class Controller;
class Graphics;

class Match{
	Graphics *graphics;
	Controller *controller;
	State *state;

	GameSettings _settings;

	bool error;
	std::vector<std::string> _errors;

	MatchStage stage;
	
	Menu subMenu;
	SubMenuOptions lastSubMenuChoice;
public:	
	Match();
	~Match();
	MatchOutput Play();
	bool load(GameSettings settings);
	std::vector<std::string> getErrors() { return _errors; }
	int getNumMoves();
private:
	void handleStart();
	void initDraw();
	void handleRunning();
	void handleSubMenu();
	MatchOutput handleEndGame();
	void saveMatch();
	void buildSubMenu();
};