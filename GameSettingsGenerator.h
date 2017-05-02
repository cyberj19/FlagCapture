#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdbool.h>

#include "enums.h"
#include "GameSettings.h"
using namespace std;

class GameSettingsGenerator {
	BoardInitOptions boardOptions;  //enum: F, R
	MovesSourceOptions movesOptions;  //enum: F, K
	string path;
	bool quiet;
	int delay;
public:
	GameSettingsGenerator(char *argv[], int argc) 
		: boardOptions(BoardInitOptions::Randomized), movesOptions(MovesSourceOptions::Keyboard), path(nullptr), quiet(false), delay(20) {}
	BoardInitOptions getBoard() const { return boardOptions; }
	MovesSourceOptions getMoves() const { return movesOptions; }
	string getPath() const { return path; }
	bool getQuiet() const;
	int getDelay() const;
	bool isAttended() const;
	GameSettings getNextSettings(bool switchKeyboardLayout, bool recording);
	bool moreSettings();
};