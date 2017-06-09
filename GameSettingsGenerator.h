#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdbool.h>
#include <vector>
#include "enums.h"
#include "GameSettings.h"
#include "BasicSettings.h"
#include <map>

const std::string boardFileExtension = "gboard";
const std::string movesAFileExtension = "moves-a_small";
const std::string movesBFileExtension = "moves-b_small";

class GameSettingsGenerator {
	BasicSettings _baseSettings;

	std::vector<std::string> _boardFileNames;
	std::vector<std::string> _movesAFileNames;
	std::vector<std::string> _movesBFileNames;

	int _currentBoardIndex;
	int _currentMovesAIndex;
	int _currentMovesBIndex;
	int _numSettings;
public:
	GameSettingsGenerator(const BasicSettings& baseSettings);
	GameSettings getNextSettings(bool recording, int round = 0);
	bool moreSettings() const { return _currentBoardIndex < _numSettings; }
	bool isQuiet() const { return _baseSettings.isQuiet(); }
	int getNumSettings() const { return _numSettings; }
	GameType getGameType();
private:
	std::string getAvailableOutputFileName(int round);
	std::string getNextMoveFile(int& currMoveFileIndex, 
		const std::vector<std::string>& moveFileNames);
};

bool doesFileExist(const std::string& name);