#pragma once
#include "State.h"
#include <conio.h>
#include "enums.h"
#include "Input.h"


class State;

class Controller {
	const char *_layoutA, *_layoutB;
	State *state;
public:
	void getInput();
	Controller(State *state, const char* layoutA, const char* layoutB);
private:
	Input parse(char ch);
};