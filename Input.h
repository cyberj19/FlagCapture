#pragma once
#include "enums.h"

class Input {
	Action action;
	Player player;
public:
	Input(Action action, Player player) : action(action), player(player) {}
	Action getAction() { return action; }
	Player getPlayer() { return player; }
};