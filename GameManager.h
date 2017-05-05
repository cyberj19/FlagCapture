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
	User UserA = User("A"), UserB = User("B");
	GameSettingsGenerator settingsGenerator;
	Menu gameMenu;
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