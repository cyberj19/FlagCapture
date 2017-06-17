#pragma once
#include <Windows.h>
#include "enums.h"
#include "GameSettings.h"
#include "Menu.h"
#include "AbstractPlayer.h"

class State;
class FilePlayer;
class Graphics;

class Match{
	Graphics *graphics;
	AbstractPlayer *_playerA, *_playerB;
	BoardData *proxyA, *proxyB;
	State *state;
	GameMove lastMove = GameMove(0, 0, 0, 0);
	GameSettings _settings;
	bool drawFlag;
	bool error;
	std::vector<std::string> _errors;

	MatchStage stage;
	
	Menu subMenu;
	SubMenuOptions lastSubMenuChoice;
public:	
	Match();
	~Match();
	MatchOutput Play();
	bool load(GameSettings settings, AbstractPlayer* playerA, AbstractPlayer* playerB);
	std::vector<std::string> getErrors() { return _errors; }
	int getLastClock();
private:
	void handleStart();
	void initDraw();
	void handleRunning();
	void handleSubMenu();
	MatchOutput handleEndGame();
	void saveMatch();
	void buildSubMenu();
	void handleLastMove();
	bool checkForEscape();
};