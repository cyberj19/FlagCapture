#pragma once
#include<string>
#include "enums.h"

class GameSettings {

	const std::string _keyboardLayoutA = "123wxad";
	const std::string _keyboardLayoutB = "789imjl";

	MovesSourceOptions _movesOptions;
	std::string _movesAInputFilePath;
	std::string _movesBInputFilePath;

	BoardInitOptions _boardOptions;
	std::string _boardInputFilePath;

	bool _recording;
	std::string _movesAOutputFilePath;
	std::string _movesBOutputFilePath;
	std::string _boardOutputFilePath;

	int _delay;
	bool _quiet;
	bool _attended;
public:
	GameSettings(int delay, bool quiet, bool attended)
		: 
		_movesOptions(MovesSourceOptions::Keyboard),
		_boardOptions(BoardInitOptions::Randomized),
		_recording(false),
		_delay(delay), 
		_quiet(quiet),
		_attended(attended)
	{}

	void setMovesInputFiles(std::string movesAInputFilePath,
							std::string movesBInputFilePath) {
		_movesOptions = MovesSourceOptions::FromFile;
		_movesAInputFilePath = movesAInputFilePath;
		_movesBInputFilePath = movesBInputFilePath;
	}

	void setBoardInputFile(std::string boardInputFilePath) {
		_boardOptions = BoardInitOptions::FromFile;
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

	const bool isAttended() { return _attended; }
	const std::string getKeyboardLayoutA() { return _keyboardLayoutA; }
	const std::string getKeyboardLayoutB() { return _keyboardLayoutB; }

	const MovesSourceOptions getMovesOptions() { return _movesOptions; }
	const std::string getMovesAInputFilePath() { return _movesAInputFilePath; }
	const std::string getMovesBInputFilePath() { return _movesBInputFilePath; }

	const BoardInitOptions getBoardInitOptions() { return _boardOptions; }
	const std::string getBoardInputFilePath() { return _boardInputFilePath; }

	const bool isRecording() { return _recording; }
	const std::string getMovesAOutputFilePath() { return _movesAOutputFilePath; }
	const std::string getMovesBOutputFilePath() { return _movesBOutputFilePath; }
	const std::string getBoardOutputFilePath() { return _boardOutputFilePath; }

	const int getDelay() { return _delay; }
	const bool isQuiet() { return _quiet; }
};