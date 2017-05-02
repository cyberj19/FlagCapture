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
	/*const static int forest_positions[22];
	const static int sea_positions[28];
	const static int forest_size;
	const static int sea_size;
	const static int flgAPos[2];
	const static int flgBPos[2];
	*/
	GameSettings _settings;

	std::vector<Position> seaPositions;
	std::vector<Position> forestPositions;
	Position flagAPosition, flagBPosition;
	std::vector<Position> soldierAPositions;
	std::vector<Position> soldierBPositions;

	std::vector<Soldier*> soldiersA, soldiersB;
	int soldierCounterA, soldierCounterB;
	GameBoard board;
	Position boardChanges[2];
	int clock;
	std::vector<Position> freePositionsA, freePositionsB;
	std::string stepsBuffer;
public:
	State(GameSettings settings) : _settings(settings), forestPositions(), seaPositions() {
		// do something with settings;
		stepsBuffer = std::string();

		if (_settings.getBoardOptions() == BoardInitOptions::FromFile) {
			// load file from 
			// settings.getBoardFilePath()
		}
		else {
			randomCells(seaPositions, Position(7, 3), Position(11, 9), 0.5);
			randomCells(forestPositions, Position(1, 3), Position(6, 9), 1);
			flagAPosition = selectCells(Position(0, 11), Position(12, 12), 1).front();
			flagBPosition = selectCells(Position(0, 0), Position(12, 1), 1).front();
		}

		initBoard();
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
	Cell& getCell(Position cellPos) { return board[cellPos.x][cellPos.y]; }
	std::string getLastStep() { return stepsBuffer; }
private:
	void initSoldiers();
	void addSoldiers(std::vector<Soldier*>& soldiersVector, Player player, std::vector<Position> positions);
	void initBoard();
	void fillCells(const std::vector<Position>& positions, CellType type);
	void updateBoardSoldierDied(Position placeOfDeath);
};