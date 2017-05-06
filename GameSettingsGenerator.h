#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdbool.h>
#include <vector>
#include "enums.h"
#include "GameSettings.h"

class GameSettingsGenerator {
	BoardInitOptions _boardOptions;  //enum: F, R
	MovesSourceOptions _movesOptions;  //enum: F, K
	std::string path;
	bool quiet;
	int delay;

	std::vector<std::string> _boardFileNames;
	std::vector<std::string> _movesAFileNames;
	std::vector<std::string> _movesBFileNames;

	int _currentSetting;
	int _maxSettings;
public:
	GameSettingsGenerator(int argc, char *argv[]);
	BoardInitOptions getBoard() const { return _boardOptions; }
	MovesSourceOptions getMoves() const { return _movesOptions; }
	std::string getPath() const { return path; }
	bool getQuiet() const;
	int getDelay() const;
	bool isAttended() const;
	GameSettings getNextSettings(bool recording, int round = 0);
	bool moreSettings();
private:
	void parseInputArguments(int argc, char *argv[]);
	std::string getAvailableOutputFileName(int round);
};