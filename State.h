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
	const static int forest_size;
	const static int sea_size;
	const static int flgAPos[2];
	const static int flgBPos[2];

	std::vector<Soldier*> soldiersA, soldiersB;
	int soldierCounterA, soldierCounterB;
	GameBoard board;
	Position boardChanges[2];
	int clock;
	std::vector<Position> freePositionsA, freePositionsB;
	std::string stepsBuffer;
	void initVectorFreePositions(std::vector<Position>& freePositions, int rowStart, int rowEnd);
public:
	State(GameSettings settings) {
		// do something with settings;
		stepsBuffer = std::string();
		reset();
	}
 	Player winner;
	bool isFinished;
	void step();
	void reset();
	void control(Input input);
	int getClock() const { return clock; }

	void updateBoardSoldierMoved(Position source, Position dest);
	void notifySoldierDied(Soldier * soldier);
	void updateLastStep(int soldierId, int dirX, int dirY);

	Position getChanges(int index) { return boardChanges[index]; }
	Cell getCell(Position cellPos) { return board[cellPos.x][cellPos.y]; }
	void initBoardPosition(Soldier* soldier);
	std::string getLastStep() { return stepsBuffer; }
private:
	void soldiersFactory();
	void addSoldiers(std::vector<Soldier*>& soldiersVector, Player player);
	void initBoard();
	void fillCells(const int *positions, int numCells, CellType type);
	void updateBoardSoldierDied(Position placeOfDeath);
};