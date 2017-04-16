#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"

#define DEFAULT_PLAYER_A_KEY_LAYOUT "123wxad"
#define DEFAULT_PLAYER_B_KEY_LAYOUT "789imjl"

void printMainMenu();

class GameManager {
	User UserA = User("A"), UserB = User("B");
	void setUserNames();
	void resetScore();
	User & getWinningUser(MenuOptions GameType, MatchOutput matchOutput);
	void startMatch(MenuOptions MatchType);
	void quitGame();
public:
	void run();
};