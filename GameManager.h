#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"
#include "GameSettingsGenerator.h"
#include "Menu.h"

//void printMainMenu();

class GameManager {
	int _round;
	User UserA = User("A"), UserB = User("B");
	GameSettingsGenerator settingsGenerator;
	Menu gameMenu;
	MenuOptions _lastChoice;
	bool recording;


	void setUserNames();
	void resetScore();
	User & getWinningUser(MenuOptions GameType, MatchOutput matchOutput);
	void startAttendedMatch(MenuOptions MatchType);
	void quitGame();

	void runAttended();
	void runUnattended();
	void buildMenu();
public:
	GameManager(GameSettingsGenerator settingsGeneator);
	void run();
};