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

	State *state;
	MovesSourceOptions _movesOptions;
	bool _recording;

	std::string movesAInputBuffer, movesBInputBuffer;
	std::string movesAOutputFilePath, movesBOutputFilePath;
public:
	Input getInput();
	Controller(State *state, GameSettings settings);
	void clearBuffer();
private:
	Input parse(char ch);
	void loadMovesFiles(std::string movesAInputFilePath, 
		std::string movesBInputFilePath);

	Input getInputFromFiles();
	Input getInputFromKeyboard();
	Input applyMove(std::string moveString);

	void getNextMoves();
};

int parseClock(std::string moveString);
