#pragma once
#include <vector>
#include "enums.h"
#include "Cell.h"
#include "Position.h"
#include "Input.h"

class Soldier;

class State {
	const static int forest_positions[22];
	const static int sea_positions[28];
	const static int flgAPos[2];
	const static int flgBPos[2];

	std::vector<Soldier*> soldiersA, soldiersB;
	GameBoard board;
	Position boardChanges[2];
	int clock;
	std::vector<Position> freePositionsA, freePositionsB;
	void initVectorFreePositions(std::vector<Position>& freePositions, int rowStart, int rowEnd) {
		freePositions = std::vector<Position>();
		for (int i = rowStart; i < rowEnd; i++) {
			for (int j = 0; j < COLS; j++) {
				if (board[i][j].getType() == CellType::EMPTY)
					freePositions.push_back(Position(i, j));
			}
		}
	}
public:
	State():clock(0), isFinished(false) {
		initBoard();
		initVectorFreePositions(freePositionsA, 0, 5);
		initVectorFreePositions(freePositionsB, 8, 13);
		soldiersFactory();
	}
 	Player winner;
	bool isFinished;
	void step();
	void control(Input input);
	const int getClock() { return clock; }
	void updateBoardSoldierMoved(Position source, Position dest);
	void updateBoardSoldierDied(Position placeOfDeath);
	Position getChanges(int index) { return boardChanges[index]; }
	Cell getCell(Position cellPos) { return board[cellPos.x][cellPos.y]; }
	void initBoardPosition(Soldier* soldier);
private:
	void soldiersFactory();
	void addSoldiers(std::vector<Soldier*>& soldiersVector, Player player);
	void initBoard();
};