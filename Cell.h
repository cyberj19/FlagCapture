#pragma once

#include "enums.h"
#define ROWS 13
#define COLS 13

class Soldier;

class Cell {
	CellType _type;
	Soldier* _soldier;
public:
	Cell(CellType type = CellType::EMPTY) : _type(type), _soldier(nullptr) {}
	const char *getSymbol();

	CellType getType() { return _type; }
	Soldier* getSoldier() { return _soldier; }

	void unsetSoldier() { _soldier = nullptr; }
	void setSoldier(Soldier* soldier) { _soldier = soldier; }
	void setType(CellType type) { _type = type; }
};