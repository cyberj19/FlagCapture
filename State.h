#pragma once
#include <vector>
#include "enums.h"
#include "Cell.h"
#include "Position.h"
#include "Input.h"
#include "GameSettings.h"

class Soldier;

void randomCells(std::vector<Position>& positions,Position UpperLeft, Position BottomRight, double prob);
std::vector<Position> selectCells(Position UpperLeft, Position BottomRight, int num);
std::vector<Position> selectCells(Position UpperLeft, Position BottomRight, GameBoard board, int num);


class State {
	GameSettings _settings;

	std::vector<Position> seaPositions;
	std::vector<Position> forestPositions;
	Position flagAPosition, flagBPosition;
	std::vector<Position> soldierAPositions;
	std::vector<Position> soldierBPositions;

	std::vector<Soldier> soldiersA, soldiersB;
	int soldierCounterA, soldierCounterB;
	GameBoard board;
	Position boardChanges[2];
	int clock;
	std::string stepsBufferA, stepsBufferB;
public:
	State(GameSettings settings);
 	Player winner;
	bool isFinished;

	//Cell& getCell(Position pos) const;
	void step();
	void reset();
	void control(Input input);
	int getClock() const { return clock; }

	void updateBoardSoldierMoved(Position source, Position dest);
	void notifySoldierDied(Soldier * soldier);
	void updateLastStep(int soldierId, int dirX, int dirY);

	Position getChanges(int index) { return boardChanges[index]; }
	Cell& getCell(Position cellPos) { return board[cellPos.getY()][cellPos.getX()]; }
	Cell& getCell(int x, int y) { return board[y][x]; }
	std::string getStepBuffer(Player player);
private:
	void initSoldiers();
	void addSoldiers(std::vector<Soldier>& soldiersVector, Player player, std::vector<Position> positions);
	void initBoard();
	void fillCells(const std::vector<Position>& positions, CellType type);
	void updateBoardSoldierDied(Position placeOfDeath);
};