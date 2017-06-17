#include "GameSettings.h"
#include "KeyboardPlayer.h"
#include "AlgorithmRegistration.h"
GameSettings& GameSettings::operator =(const GameSettings &settings) {
	_delay = settings._delay;
	_quiet = settings._quiet;
	_gameType = settings._gameType;

	_inputOptionA = settings._inputOptionA;
	_inputOptionB = settings._inputOptionB;
	_movesAInputFilePath = settings._movesAInputFilePath;
	_movesBInputFilePath = settings._movesBInputFilePath;

	_boardOptions = settings._boardOptions;
	_boardInputFilePath = settings._boardInputFilePath;

	_recording = settings._recording;
	_movesAOutputFilePath = settings._movesAOutputFilePath;
	_movesBOutputFilePath = settings._movesBOutputFilePath;
	_boardOutputFilePath = settings._boardOutputFilePath;

	return *this;
}