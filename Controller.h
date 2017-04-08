#pragma once
#include "Match.h"

enum class Action{CHOOSE1, CHOOSE2, CHOOSE3, UP, DOWN, LEFT, RIGHT};

typedef struct input {
	Action action;
	Player player;
}Input;
class Controller {
	char *_layoutA, *_layoutB;
public:
	Input getInput();
	Controller(const char* layoutA, const char* layoutB);
};