#include "GameSettingsGenerator.h"
#include <Windows.h>
#include <algorithm>
using namespace std;

void getFilesList(string filePath, string extension, vector<string> & returnFileName)
{
	WIN32_FIND_DATA fileInfo;
	HANDLE hFind;
	string fullPath = filePath + "\\" + extension;
	hFind = FindFirstFile(fullPath.c_str(), &fileInfo);
	if (hFind != INVALID_HANDLE_VALUE) {
		returnFileName.push_back(filePath + "\\" + fileInfo.cFileName);
		while (FindNextFile(hFind, &fileInfo) != 0) {
			returnFileName.push_back(filePath + "\\" + fileInfo.cFileName);
		}
	}

	sort(begin(returnFileName), end(returnFileName));
}

bool doesFileExist(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

GameSettingsGenerator::GameSettingsGenerator(int argc, char *argv[])
	: _boardOptions(BoardInitOptions::Randomized),
	_movesOptions(MovesSourceOptions::Keyboard),
	path(""),
	quiet(false),
	delay(20),
	_boardFileNames(),
	_movesAFileNames(),
	_movesBFileNames(),
	_currentSetting(0),
	_maxSettings(0)
{
	parseInputArguments(argc, argv);

	if (_boardOptions == BoardInitOptions::FromFile)
		getFilesList(path, "*.gboard", _boardFileNames);

	if (_movesOptions == MovesSourceOptions::FromFile) {
		getFilesList(path, "*.moves-a", _movesAFileNames);
		getFilesList(path, "*.moves-b", _movesBFileNames);
	}

	_maxSettings = max(_boardFileNames.size(), max(_movesAFileNames.size(), _movesBFileNames.size()));
}

bool GameSettingsGenerator::getQuiet() const
{
	//quiet is active only if -board f -moves f
	if (_boardOptions == BoardInitOptions::FromFile && _movesOptions == MovesSourceOptions::FromFile) {
		return quiet;
	}
	return false;
}

int GameSettingsGenerator::getDelay() const
{
	//if quiet is active (true) - delay is ignored
	return (quiet) ? 0 : delay;
}

bool GameSettingsGenerator::isAttended() const
{
	return _movesOptions == MovesSourceOptions::Keyboard;
}

GameSettings GameSettingsGenerator::getNextSettings(bool recording, int round)
{
	GameSettings settings = GameSettings(delay, quiet, isAttended());

	if (_boardOptions == BoardInitOptions::FromFile) {
		settings.setBoardInputFile(_boardFileNames[_currentSetting]);
	}

	if (_movesOptions == MovesSourceOptions::FromFile) {
		settings.setMovesInputFiles(_movesAFileNames[_currentSetting],
			_movesBFileNames[_currentSetting]);
	}

	if (recording) {
		string fname = getAvailableOutputFileName(round);
		settings.setRecordingOutputFiles(fname + ".gboard",
			fname + ".moves-a",
			fname + ".moves-b");
	}
	++_currentSetting;

	return settings;
}

bool GameSettingsGenerator::moreSettings()
{
	return _currentSetting < _maxSettings;
}

void GameSettingsGenerator::parseInputArguments(int argc, char * argv[])
{
	for (int i = 1; i < argc; ) {
		if (strcmp(argv[i], "-board") == 0) {
			if (i == argc - 1) {
				//error;
			}
			else if (strcmp(argv[i + 1], "f") == 0) {
				_boardOptions = BoardInitOptions::FromFile;
			}
			else if (strcmp(argv[i + 1], "r") == 0) {
				_boardOptions = BoardInitOptions::Randomized;
			}
			else {
				//error;
			}
			i += 2;
		}
		else if (strcmp(argv[i], "-moves") == 0) {
			if (i == argc - 1) {
				//error;
			}
			else if (strcmp(argv[i + 1], "f") == 0) {
				_movesOptions = MovesSourceOptions::FromFile;
			}
			else if (strcmp(argv[i + 1], "k") == 0) {
				_movesOptions = MovesSourceOptions::Keyboard;
			}
			else {
				//error;
			}
			i += 2;
		}
		else if (strcmp(argv[i], "-path") == 0) {

			if (i == argc - 1) {
				//error;
			}
			else {
				path = std::string(argv[i + 1]);
				if (path.front() == '\"' || path.back() == '\"') {
					if (path.back() != path.front()) {
						// error
					}
					else {
						path.pop_back();
						path.erase(0, 1);
					}
				}
				if (path.back() == '\\')
					path.pop_back();
			}
			i += 2;
		}
		else if (strcmp(argv[i], "-quiet") == 0) {
			//quiet is active only if -board f -moves f
			quiet = true;
			i += 1;
		}
		else if (strcmp(argv[i], "-delay") == 0) {
			//if quiet is active - delay is ignored
			//default is 20 ms
			if (i == argc - 1) {
				//error;
			}
			else {
				delay = atoi(argv[i + 1]);//convert from char to int
			}
			i += 2;
		}
		else {
			//the command line isn't valid
			//error
		}
	}
}

std::string GameSettingsGenerator::getAvailableOutputFileName(int round)
{
	
	string new_name = path + "\\record-" + to_string(round);;
	while (doesFileExist(new_name + ".gboard") ||
		doesFileExist(new_name + ".moves-a") ||
		doesFileExist(new_name + ".moves-b"))
		new_name += "-new";
	return new_name;
}
