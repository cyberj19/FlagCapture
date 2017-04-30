#pragma once
#include "State.h"
#include <conio.h>
#include "enums.h"
#include "Input.h"
#include <string>
using namespace std;

class State;

class Controller {
	const string _layoutA, _layoutB;
	State *state;
public:
	Input getInput();
	Controller(State *state, const string layoutA, const string layoutB);
	void clearBuffer();
private:
	Input parse(char ch);
};