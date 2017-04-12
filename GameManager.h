#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"




class GameManager {
	User UserA = User("A"), UserB = User("B");
	int getMenuChoice();
	void setUserNames();
	void resetScore();
	void startMatch(int MatchType);
public:
	void run();
};