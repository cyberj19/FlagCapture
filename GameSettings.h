class GameSettings {
	char *keyboardLayoutA;
	char *keyboardLayoutB;

	MovesSourceOptions movesOptions;
	string _movesAInputFilePath;
	string _movesBInputFilePath;

	BoardInitOptions boardOptions;
	string boardFilePath;

	bool recording;
	string movesAOutputFilePath;
	string movesBOutputFilePath;
	
	int delay;
	bool quiet;
public:
	GameSettings(char *keyboardLayoutA, char *keyboardLayoutB,
		MovesSourceOptions movesOptions, 
		string movesAInputFilePath,
		string movesBInputFilePath,
		BoardInitOptions boardOptions,
		string boardFilePath,
		bool recording,
		string movesAOutputFilePath,
		string movesBOutputFilePath,
		int delay,
		bool quiet)
		: keyboardLayoutA(keyboardLayoutA), keyboardLayoutB(keyboardLayoutB),
		movesOptions(movesOptions), 
		_movesAInputFilePath(movesAInputFilePath), 
		_movesBInputFilePath(movesBInputFilePath),
		boardOptions(boardOptions), boardFilePath(boardFilePath),
		recording(recording), 
		movesAOutputFilePath(movesAOutputFilePath),
		movesBOutputFilePath(movesBOutputFilePath),
		delay(delay), quiet(quiet)
	{}

	const char *getKeyboardLayoutA() { return keyboardLayoutA; }
	const char *getKeyboardLayoutB() { return keyboardLayoutB; }

	const MovesSourceOptions getMovesOptions() { return movesOptions; }
	const string getMovesAInputFilePath() { return _movesAInputFilePath; }
	const string getMovesBInputFilePath() { return _movesBInputFilePath; }

	const BoardInitOptions getBoardOptions() { return boardOptions; }
	const string getBoardFilePath() { return boardFilePath; }

	const bool isRecording() { return recording; }
	const string getMovesAOutputFilePath() { return movesAOutputFilePath; }
	const string getMovesBOutputFilePath() { return movesBOutputFilePath; }
	const int getDelay() { return delay; }
	const bool isQuiet() { return quiet; }

	void switchKeyboardLayouts();
};