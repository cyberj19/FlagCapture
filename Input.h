#pragma once
#include "enums.h"

class Input {
	Action action;
	Player203398664 player;
public:
	Input(Action action, Player203398664 player) : action(action), player(player) {}
	Action getAction() { return action; }
	Player203398664 getPlayer() { return player; }
};