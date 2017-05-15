#include "GameSettingsGenerator.h"
#include <Windows.h>
#include <algorithm>
#include <map>
#include "Utils.h"
using namespace std;

string fullPath(string dirPath, string fileName) {
	return dirPath + (dirPath == "" ? "" : "\\") + fileName;
}

void getFilesList(string filePath, string extension, vector<string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	string fileTemplate = fullPath(filePath, string("*.") + extension);
	hFind = FindFirstFile(fileTemplate.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			returnFileName.push_back(fullPath(filePath, fileInfo.cFileName));
		} while (FindNextFile(hFind, &fileInfo) != 0); 
	}

	sort(begin(returnFileName), end(returnFileName));
}

bool doesFileExist(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

GameSettingsGenerator::GameSettingsGenerator(const BasicSettings& baseSettings)
	: _baseSettings(baseSettings),
	_boardFileNames(),
	_movesAFileNames(),_movesBFileNames(),
	_currentBoardIndex(0), _currentMovesAIndex(0), _currentMovesBIndex(0),
	_numSettings(0)
{
	if (baseSettings.getBoardOptions() == BoardOptions::FromFile)
	{
		getFilesList(baseSettings.getPath(), boardFileExtension, _boardFileNames);
		_numSettings = (int) _boardFileNames.size();
	}

	if (baseSettings.getInputOptions() == InputOptions::FromFile) {
		getFilesList(baseSettings.getPath(), movesAFileExtension, _movesAFileNames);
		getFilesList(baseSettings.getPath(), movesBFileExtension, _movesBFileNames);
	}

	if (_numSettings == 0 && 
		baseSettings.getBoardOptions() != BoardOptions::FromFile) 
		_numSettings = 1;
}

GameSettings GameSettingsGenerator::getNextSettings(bool recording, int round) {
	if (_currentBoardIndex == _numSettings) _currentBoardIndex = 0;

	GameSettings settings = GameSettings(_baseSettings.getDelay(), _baseSettings.isQuiet(), isAttended());

	if (_baseSettings.getBoardOptions() == BoardOptions::FromFile) {
		settings.setBoardInputFile(_boardFileNames[_currentBoardIndex]);
	}

	if (_baseSettings.getInputOptions() == InputOptions::FromFile) {
		settings.setMovesInputFiles(
			getNextMoveFile(_currentMovesAIndex, _movesAFileNames),
			getNextMoveFile(_currentMovesBIndex, _movesBFileNames));
	}

	if (recording) {
		string fname = getAvailableOutputFileName(round);
		settings.setRecordingOutputFiles(fname + "." + boardFileExtension,
										fname + "." + movesAFileExtension,
										fname + "." + movesBFileExtension);
	}
	_currentBoardIndex++;
	
	return settings;
}

std::string GameSettingsGenerator::getAvailableOutputFileName(int round) {
	string new_name = fullPath(_baseSettings.getPath(), string("record-") + to_string(round));
	while (doesFileExist(new_name + "." +  boardFileExtension) ||
		doesFileExist(new_name + "." + movesAFileExtension) ||
		doesFileExist(new_name + "." + movesBFileExtension))
		new_name += "-new";
	return new_name;
}

string GameSettingsGenerator::getNextMoveFile(int& currMoveFileIndex, 
	const std::vector<std::string>& moveFileNames)
{
	string ref = stripExtension(_boardFileNames[_currentBoardIndex]);
	for (; currMoveFileIndex < moveFileNames.size(); currMoveFileIndex++) {
		string curr = stripExtension(moveFileNames[currMoveFileIndex]);
		if (curr == ref)
			return moveFileNames[currMoveFileIndex];
		else if (curr > ref)
			break;
	}
	return string("");
}
