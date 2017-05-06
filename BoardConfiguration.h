#pragma once
#include <vector>
#include "Position.h"
#include "GameSettings.h"
#include "enums.h"
#include "GameBoard.h"


void randomCells(std::vector<Position>& positions, Position UpperLeft, Position BottomRight, double prob);
std::vector<Position> selectCells(Position UpperLeft, Position BottomRight, int num);

class BoardConfiguration {
	BoardInitOptions _boardInitOptions;

	std::vector<Position> _seaPositions;
	std::vector<Position> _forestPositions;

	Position _flagAPosition;
	Position _flagBPosition;

	std::vector<Position> _soldierAPositions;
	std::vector<Position> _soldierBPositions;

public:
	BoardConfiguration();
	
	int loadSettings(GameSettings settings);

	std::vector<Position> getSeaPositions() const { return _seaPositions; }
	std::vector<Position> getForestPositions() const { return _forestPositions; }

	std::vector<Position> getSoldiersAPositions();
	std::vector<Position> getSoldiersBPositions();

	Position getFlagAPosition() const { return _flagAPosition; }
	Position getFlagBPosition() const { return _flagBPosition; }
private:
	void generateRandomPositions();
	int loadPositionsFromFile(std::string inputFile);

	std::vector<Position> selectFreePositions(Position UpperLeft, Position BottomRight, int num);
};