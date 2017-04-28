#pragma once
#include <Windows.h>
#include <conio.h>
#include <iostream>
#include "User.h"
#include "Match.h"
#include "enums.h"

#define DEFAULT_PLAYER_A_KEY_LAYOUT "123wxad"
#define DEFAULT_PLAYER_B_KEY_LAYOUT "789imjl"

//TO DO: in c++
//const string DEFAULT_PLAYER_A_KEY_LAYOUT = "123wxad;
//const string DEFAULT_PLAYER_B_KEY_LAYOUT = "789imjl";

//if it doesn't work, try:
//maybe we can put all the constants here
//class Constants {
//   static const DefaultPlayerAKeyLayout = "123wxad";
//   static const DefaultPlayerBKeyLayout = "789imjl";
//};

//cout << Constants::DefaultPlayerLayout << endl;

//The first one is better, but we need to try what works



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
