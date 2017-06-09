#pragma once
#include<string>
#include "enums.h"

class GameSettings {

	const std::string _keyboardLayoutA = "123wxad";
	const std::string _keyboardLayoutB = "789imjl";

	InputOptions _movesOptions;
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
	bool _attended;
public:
	GameSettings& operator =(const GameSettings &settings) {
		_delay = settings._delay;
		_quiet = settings._quiet;
		_attended = settings._attended;

		_movesOptions = settings._movesOptions;
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

	GameSettings(int delay = 100, bool quiet = false, bool attended = true)
		: 
		_movesOptions(InputOptions::Keyboard),
		_boardOptions(BoardOptions::Randomized),
		_recording(false),
		_delay(delay), 
		_quiet(quiet),
		_attended(attended)
	{}

	void setMovesInputFiles(std::string movesAInputFilePath,
							std::string movesBInputFilePath) {
		_movesOptions = InputOptions::FromFile;
		_movesAInputFilePath = movesAInputFilePath;
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

	const bool isAttended() const { return _attended; }
	const std::string getKeyboardLayoutA() const { return _keyboardLayoutA; }
	const std::string getKeyboardLayoutB() const { return _keyboardLayoutB; }

	const InputOptions getMovesOptions() const { return _movesOptions; }
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
};