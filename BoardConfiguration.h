#pragma once
#include <vector>
#include "Position.h"
#include "GameSettings.h"
#include "enums.h"
#include "GameBoard.h"


void randomCells(std::vector<Position>& positions, Position UpperLeft, Position BottomRight, double prob);
std::vector<Position> selectCells(Position UpperLeft, Position BottomRight, int num);
std::vector<Position> selectCells(Position UpperLeft, Position BottomRight, GameBoard board, int num);

class BoardConfiguration {
	GameBoard& _board;
	BoardInitOptions _boardInitOptions;

	std::vector<Position> _seaPositions;
	std::vector<Position> _forestPositions;

	Position _flagAPosition;
	Position _flagBPosition;

	std::vector<Position> _soldierAPositions;
	std::vector<Position> _soldierBPositions;

public:
	BoardConfiguration(GameSettings settings, GameBoard& board);
	
	std::vector<Position> getSeaPositions() const { return _seaPositions; }
	std::vector<Position> getForestPositions() const { return _forestPositions; }

	std::vector<Position> getSoldiersAPositions() const;
	std::vector<Position> getSoldiersBPositions() const;

	Position getFlagAPosition() const { return _flagAPosition; }
	Position getFlagBPosition() const { return _flagBPosition; }
private:
	void generateRandomPositions();
	void loadPositionsFromFile();
};