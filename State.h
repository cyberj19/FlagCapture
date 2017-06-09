#pragma once
#include <vector>
#include "enums.h"
#include "Cell.h"
#include "Position.h"
#include "Input.h"
#include "GameSettings.h"
#include "Soldier.h"
#include "BoardConfiguration.h"
#include "Board.h"

class State {
	GameSettings _settings;
	
	BoardConfiguration _boardConfig;

	std::vector<Soldier> soldiersA, soldiersB;
	int soldierCounterA, soldierCounterB;
	Board::GameBoard board;

	std::vector<Position> _changeBuffer;
	int clock;
	std::string stepsBufferA, stepsBufferB;
public:
	State(GameSettings settings, BoardConfiguration boardConfig);
	Player winner;
	bool isFinished;
	bool anyMoving();
	void step(GameMove move);
	void reset();
	int getClock() const { return clock; }

	void updateBoardSoldierMoved(Position source, Position dest);
	void notifySoldierDied(Soldier * soldier);
	void recordAction(int soldierId, Action action);

	Position popChange();
	bool hasChanges() { return !_changeBuffer.empty(); }
	Cell& getCell(Position cellPos) { return board[cellPos.getY()][cellPos.getX()]; }
	Cell& getCell(int x, int y) { return board[y][x]; }
	std::string getStepBuffer(Player player);
	std::string getBoardString();
private:
	void initRecorder();
	void initGameObjects();
	void initTeams();
	void initBoard();

	void resetRecorder();
	void resetGameObjects();

	void createSoldiers(std::vector<Soldier>& soldiersVector, Player player, std::vector<Position> positions);
	void fillCells(const std::vector<Position>& positions, CellType type);
	void updateBoardSoldierDied(Position placeOfDeath);
};