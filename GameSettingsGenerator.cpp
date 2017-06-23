#include "GameSettingsGenerator.h"
#include <Windows.h>
#include <algorithm>
#include <map>
#include "Utils.h"
using namespace std;

string fullPath(string dirPath, string fileName) {
	return dirPath + (dirPath == "" ? "" : "\\") + fileName;
}

void getFilesList(string filePath, string extension, 
	vector<string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	string fileTemplate = fullPath(filePath, string("*.") + extension);
	hFind = FindFirstFileA(fileTemplate.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			returnFileName.push_back(fullPath(filePath, fileInfo.cFileName));
		} while (FindNextFileA(hFind, &fileInfo) != 0); 
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
	_movesAFileNames(), _movesBFileNames(),
	_currentBoardIndex(0), _currentMovesAIndex(0), _currentMovesBIndex(0),
	_numSettings(0)
{
	if (baseSettings.getBoardOptions() == BoardOptions::FromFile)
	{
		getFilesList(baseSettings.getPath(), boardFileExtension, _boardFileNames);
		_numSettings = (int) _boardFileNames.size();
	}
	else if (getGameType() == GameType::AlgorithmGame) {
		_numSettings = baseSettings.getNumRounds();
		if (_numSettings <= 0)
			throw "No rounds were set for algorithm game";
	}

	if (baseSettings.getInputOptionA() == InputOptions::FromFile)
		getFilesList(baseSettings.getPath(), movesAFileExtension, _movesAFileNames);
	if (baseSettings.getInputOptionB() == InputOptions::FromFile)
		getFilesList(baseSettings.getPath(), movesBFileExtension, _movesBFileNames);


	if (_numSettings == 0 && 
		baseSettings.getBoardOptions() != BoardOptions::FromFile) 
		_numSettings = 1;

	if (baseSettings.getBoardOptions() == BoardOptions::Randomized)
		_numSettings = baseSettings.getNumRounds();

	if (_numSettings == 0)
		throw "No settings are available for gameplay";
}

GameSettings GameSettingsGenerator::getNextSettings(bool recording, int round) {
	if (_currentBoardIndex == _numSettings) _currentBoardIndex = 0;

	GameSettings settings = GameSettings(_baseSettings.getDelay(),
		_baseSettings.isQuiet(), getGameType());

	if (_baseSettings.getBoardOptions() == BoardOptions::FromFile) {
		settings.setBoardInputFile(_boardFileNames[_currentBoardIndex]);
	}


	if (_baseSettings.getInputOptionA() == InputOptions::FromFile)
		settings.setMovesInputFileA(getNextMoveFile(_currentMovesAIndex, _movesAFileNames));
	else
		settings.setInputOptionA(_baseSettings.getInputOptionA());

	if (_baseSettings.getInputOptionB() == InputOptions::FromFile)
		settings.setMovesInputFileB(getNextMoveFile(_currentMovesBIndex, _movesBFileNames));
	else
		settings.setInputOptionB(_baseSettings.getInputOptionB());


	if (recording || _baseSettings.shouldSave()) {
		string fname = getAvailableOutputFileName(round);
		settings.setRecordingOutputFiles(fname + "." + boardFileExtension,
										fname + "." + movesAFileExtension,
										fname + "." + movesBFileExtension);
	}
	_currentBoardIndex++;
	
	return settings;
}

GameType GameSettingsGenerator::getGameType()
{
	//check is attended
	if (_baseSettings.getInputOptionA() == InputOptions::Keyboard
		|| _baseSettings.getInputOptionB() == InputOptions::Keyboard)
		return GameType::Attended;

	//check if both algorithm
	if (_baseSettings.getInputOptionA() == InputOptions::Algorithm
		&& _baseSettings.getInputOptionB() == InputOptions::Algorithm)
		return GameType::AlgorithmGame;

	return GameType::FileGame;
}

std::string GameSettingsGenerator::getAvailableOutputFileName(int round) {
	string new_name = fullPath(_baseSettings.getPath(), string("record-") + to_string(round));
	while (	doesFileExist(new_name + "." +  boardFileExtension) ||
			doesFileExist(new_name + "." + movesAFileExtension) ||
			doesFileExist(new_name + "." + movesBFileExtension))
		new_name += "-new";
	return new_name;
}

string GameSettingsGenerator::getNextMoveFile(int& currMoveFileIndex, 
	const std::vector<std::string>& moveFileNames)
{
	// find next move file which's name matches the current _board file
	string ref = stripExtension(_boardFileNames[_currentBoardIndex]);
	for (; currMoveFileIndex < (int) moveFileNames.size(); currMoveFileIndex++) {
		string curr = stripExtension(moveFileNames[currMoveFileIndex]);

		if (curr == ref)
			return moveFileNames[currMoveFileIndex];
		else if (curr > ref)
			break;
	}
	return string("");
}
