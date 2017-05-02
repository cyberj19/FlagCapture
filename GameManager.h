#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"
#include "GameSettingsGenerator.h"

const char* DEFAULT_PLAYER_A_KEY_LAYOUT = "123wxad";
const char* DEFAULT_PLAYER_B_KEY_LAYOUT = "789imjl";

void printMainMenu();

class GameManager {
	User UserA = User("A"), UserB = User("B");
	GameSettingsGenerator settingsGenerator;
	bool recording;

	void setUserNames();
	void resetScore();
	User & getWinningUser(MenuOptions GameType, MatchOutput matchOutput);
	void startAttendedMatch(MenuOptions MatchType);
	void quitGame();

	void runAttended();
	void runUnattended();
public:
	GameManager(GameSettingsGenerator settingsGeneator);
	void run();
};