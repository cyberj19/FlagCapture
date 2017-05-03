#pragma once
#include<string>
class GameSettings {

	const char* _keyboardLayoutA = "123wxad";
	const char* _keyboardLayoutB = "789imjl";

	MovesSourceOptions _movesOptions;
	std::string _movesAInputFilePath;
	std::string _movesBInputFilePath;

	BoardInitOptions _boardOptions;
	std::string _boardFilePath;

	bool _recording;
	std::string _movesAOutputFilePath;
	std::string _movesBOutputFilePath;
	std::string _boardOutputFilePath;

	int _delay;
	bool _quiet;
public:
	GameSettings(int delay, bool quiet)
		: 
		_movesOptions(MovesSourceOptions::Keyboard),
		_boardOptions(BoardInitOptions::Randomized),
		_recording(false),
		_delay(delay), 
		_quiet(quiet)
	{}

	void setMovesInputFiles(std::string movesAInputFilePath,
							std::string movesBInputFilePath) {
		_movesOptions = MovesSourceOptions::FromFile;
		_movesAInputFilePath = movesAInputFilePath;
		_movesBInputFilePath = movesBInputFilePath;
	}

	void setBoardInputFile(std::string boardInputFilePath) {
		_boardOptions = BoardInitOptions::FromFile;
		_boardFilePath = boardInputFilePath;
	}

	void setRecordingOutputFiles(std::string boardOutputFilePath,
								 std::string movesAOutputFilePath,
								 std::string movesBOutputFilePath) {
		_recording = true;
		_boardOutputFilePath = boardOutputFilePath;
		_movesAOutputFilePath = movesAOutputFilePath;
		_movesBOutputFilePath = movesBOutputFilePath;
	}

	const char *getKeyboardLayoutA() { return _keyboardLayoutA; }
	const char *getKeyboardLayoutB() { return _keyboardLayoutB; }

	const MovesSourceOptions getMovesOptions() { return _movesOptions; }
	const std::string getMovesAInputFilePath() { return _movesAInputFilePath; }
	const std::string getMovesBInputFilePath() { return _movesBInputFilePath; }

	const BoardInitOptions getBoardOptions() { return _boardOptions; }
	const std::string getBoardFilePath() { return _boardFilePath; }

	const bool isRecording() { return _recording; }
	const std::string getMovesAOutputFilePath() { return _movesAOutputFilePath; }
	const std::string getMovesBOutputFilePath() { return _movesBOutputFilePath; }
	const int getDelay() { return _delay; }
	const bool isQuiet() { return _quiet; }
};