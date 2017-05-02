#pragma once
#include "State.h"
#include <conio.h>
#include "enums.h"
#include "Input.h"
#include "GameSettings.h"
#include<string>
class State;

class Controller {
	const char *_layoutA, *_layoutB;
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
};