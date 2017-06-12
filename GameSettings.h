#pragma once
#include<string>
#include "enums.h"
#include "AlgorithmPlayer.h"

class GameSettings {

	const std::string _keyboardLayoutA = "123wxad";
	const std::string _keyboardLayoutB = "789imjl";

	InputOptions _inputOptionA;
	InputOptions _inputOptionB;

	std::string _movesAInputFilePath;
	std::string _movesBInputFilePath;

	BoardOptions _boardOptions;
	std::string _boardInputFilePath;

	bool _recording;
	std::string _movesAOutputFilePath;
	std::string _movesBOutputFilePath;
	std::string _boardOutputFilePath;

	int _delay;
	bool _quiet;
	GameType _gameType;
public:
	GameSettings& operator =(const GameSettings &settings);

	GameSettings(int delay = 100, bool quiet = false, 
		GameType gameType = GameType::Attended)
		: 
		_inputOptionA(InputOptions::Keyboard),
		_inputOptionB(InputOptions::Keyboard),
		_boardOptions(BoardOptions::Randomized),
		_recording(false),
		_delay(delay), 
		_quiet(quiet),
		_gameType(gameType)
	{}

	void setMovesInputFileA(const std::string& movesAInputFilePath) {
		_inputOptionA = InputOptions::FromFile;
		_movesAInputFilePath = movesAInputFilePath;
	}
	
	void setMovesInputFileB(const std::string& movesBInputFilePath) {
		_inputOptionB = InputOptions::FromFile;
		_movesBInputFilePath = movesBInputFilePath;
	}

	void setBoardInputFile(std::string boardInputFilePath) {
		_boardOptions = BoardOptions::FromFile;
		_boardInputFilePath = boardInputFilePath;
	}

	void setRecordingOutputFiles(std::string boardOutputFilePath,
								 std::string movesAOutputFilePath,
								 std::string movesBOutputFilePath) {
		_recording = true;
		_boardOutputFilePath = boardOutputFilePath;
		_movesAOutputFilePath = movesAOutputFilePath;
		_movesBOutputFilePath = movesBOutputFilePath;
	}

	const GameType getGameType() const { return _gameType; }
	const std::string getKeyboardLayoutA() const { return _keyboardLayoutA; }
	const std::string getKeyboardLayoutB() const { return _keyboardLayoutB; }

	const InputOptions getInputOptionA() const { return _inputOptionA; }
	const InputOptions getInputOptionB() const { return _inputOptionB; }

	void setInputOptionA(InputOptions opt) { _inputOptionA = opt; }
	void setInputOptionB(InputOptions opt) { _inputOptionB = opt; }

	const std::string getMovesAInputFilePath() const { return _movesAInputFilePath; }
	const std::string getMovesBInputFilePath() const { return _movesBInputFilePath; }

	const BoardOptions getBoardInitOptions() const { return _boardOptions; }
	const std::string getBoardInputFilePath() const { return _boardInputFilePath; }

	const bool isRecording() const { return _recording; }
	const std::string getMovesAOutputFilePath() const { return _movesAOutputFilePath; }
	const std::string getMovesBOutputFilePath() const { return _movesBOutputFilePath; }
	const std::string getBoardOutputFilePath() const { return _boardOutputFilePath; }

	const int getDelay() const { return _delay; }
	const bool isQuiet() const { return _quiet; }

	AbstractPlayer* getPlayerA() const;
	AbstractPlayer* getPlayerB() const;
};