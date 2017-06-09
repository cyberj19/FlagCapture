#pragma once
#include "BoardData.h"
#include "State.h"
class StateProxy : public BoardData {
	State* _state;
	Player _player;

public:
	StateProxy(State* state, Player player) : _state(state), _player(player) {}
	virtual char charAt(int x, int y) const {
		Cell cell = _state->getCell(x - 1, y - 1);
		Soldier* soldier = cell.getSoldier();

		if (soldier == nullptr) {
			if (cell.getType() == CellType::FOREST) return 'T';
			else if (cell.getType() == CellType::SEA) return 'S';
			else return ' ';
		}
		else if (soldier->getPlayer() == _player) {
			return '0' + soldier->getId();
		}
		else return '#';
	}
};