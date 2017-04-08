#pragma once

#include "User.h"
#include "Match.h"

class GameManager {
	enum { ESC = 27 };
	User UserA = User("A"), UserB = User("B");
	int getMenuChoice();
	void setUserNames();
	void resetScore();
	void startMatch(int MatchType);
public:
	void run();
};