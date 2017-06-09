#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"
#include "GameSettingsGenerator.h"
#include "Menu.h"

class GameManager {
	int _round;
	User UserA, UserB;
	GameSettingsGenerator settingsGenerator;
	Menu gameMenu;
	MenuOptions _lastChoice;
	bool recording;
public:
	GameManager(GameSettingsGenerator settingsGeneator);
	void run();
private:
	void setUserNames();
	void resetScore();
	User & getWinningUser(MenuOptions GameType, MatchOutput matchOutput);
	void startAttendedMatch(MenuOptions MatchType);
	void startMatch(const GameSettings& settings, MenuOptions MatchType = MenuOptions::REGULAR_GAME);
	void quitGame();
	void runAttendedGame();
	void runFileGame();
	void runAlgorithmGame();
	void buildMenu();
};
