#pragma once
#include "Soldier.h"
#include "Controller.h"


#define ROWS 13
#define COLS 13

class Soldier;

enum class CellType {EMPTY, FOREST, SEA, FLAG_A, FLAG_B};
typedef struct cell{
	CellType type;
	Soldier* soldier;
} Cell;

class State {
	Soldier *soldiersA, *soldiersB;
	Cell board[ROWS][COLS];
	int movingSoldierIndexA, movingSoldierIndexB;
public:
	Player winner;
	bool isFinished;
	void step();
	void control(Input input);
};