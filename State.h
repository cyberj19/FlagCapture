#pragma once
#include "Soldier.h"
#include "Controller.h"
#include <vector>


#define ROWS 13
#define COLS 13

class Soldier;

enum class CellType {EMPTY, FOREST, SEA, FLAG_A, FLAG_B};
typedef struct cell{
	CellType type;
	Soldier* soldier;
} Cell;

class State {
	std::vector<Soldier&> soldiersA, soldiersB;
	Cell board[ROWS][COLS];
	int movingSoldierIndexA, movingSoldierIndexB;
	int clock;
public:
	State():clock(0){}
	Player winner;
	bool isFinished;
	void step();
	void control(Input input);
	const int getClock() { return clock; }
};