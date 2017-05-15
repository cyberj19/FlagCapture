#pragma once
#include "State.h"
#include <conio.h>
#include "enums.h"
#include "Input.h"
#include "GameSettings.h"
#include<string>
#include "Utils.h"
class State;

class Controller {
	std::string _layoutA, _layoutB;
	std::vector<std::string> _movesAList, _movesBList;
	int _nextMoveA, _nextMoveB;
	int _moveCounter;
	State *_state;
	InputOptions _inputOptions;
	bool _recording;
public:
	Input getInput();
	Controller(State *state, const GameSettings& settings);
	void clearBuffer();
	bool eof() {
		return _inputOptions == InputOptions::FromFile && _nextMoveA == -1 &&
			_nextMoveB == -1;
	}
	int getNumMoves() { return _moveCounter; }
private:
	Input parseKey(char ch);
	void loadMovesFiles(std::string movesAInputFilePath, 
		std::string movesBInputFilePath);

	Input applyNextMove(int & nextMove, std::vector<std::string>& moves);

	Input getInputFromFiles();
	Input getInputFromKeyboard();
	Input applyMove(std::string moveString);

	void getNextMoves();
};

int parseClock(std::string moveString);
