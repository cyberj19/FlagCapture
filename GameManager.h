#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"

const string DEFAULT_PLAYER_A_KEY_LAYOUT = "123wxad";
const string DEFAULT_PLAYER_B_KEY_LAYOUT = "789imjl";

void printMainMenu();

class GameManager {
	User UserA = User("A"), UserB = User("B");
	void setUserNames();
	void resetScore();
	const User & getWinningUser(MenuOptions GameType, MatchOutput matchOutput) const;
	void startMatch(MenuOptions MatchType);
	void quitGame();
public:
	void run();
};