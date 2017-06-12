#include "GameSettings.h"
#include "KeyboardPlayer.h"
#include "AlgorithmRegistration.h"
AbstractPlayer * GameSettings::getPlayerA() const
{
	AbstractPlayer *playerA;
	if (_inputOptionA == InputOptions::Keyboard)
		playerA = new KeyboardPlayer(*this);
	else // Algorithm
		playerA = new AlgorithmPlayer(); // AlgorithmRegistration::nextAlgorithm();
	playerA->setPlayer(1);
	return playerA;
}
AbstractPlayer * GameSettings::getPlayerB() const
{
	AbstractPlayer *playerB;
	if (_inputOptionB == InputOptions::Keyboard)
		playerB = new KeyboardPlayer(*this);
	else // Algorithm
		playerB = AlgorithmRegistration::nextAlgorithm();
	playerB->setPlayer(2);
	return playerB;
}

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