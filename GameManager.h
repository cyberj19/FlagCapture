#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"
#include <string>




class GameManager {
	User UserA = User("A"), UserB = User("B");
	int getMenuChoice();
	void setUserNames();
	void startMatch(int MatchType);
	void resetScore();
public:
	void run();
private:
	void increaseScoreToTheWinner(int GameType, Player winner);
	bool isUserAwinner(int GameType, Player winner);
};

