#include "BoardConfiguration.h"
#include <vector>
#include <time.h>
using namespace std;

BoardConfiguration::BoardConfiguration() {}

int BoardConfiguration::loadSettings(GameSettings settings)
{
	_boardInitOptions = settings.getBoardInitOptions();
	if (_boardInitOptions == BoardInitOptions::FromFile)
		return loadPositionsFromFile(settings.getBoardInputFilePath());
	else
		generateRandomPositions();
	return 0;
}

std::vector<Position> BoardConfiguration::getSoldiersAPositions()
{
	if (_boardInitOptions == BoardInitOptions::FromFile)
		return _soldierAPositions;
	else
		return selectFreePositions(Position(0, 0), Position(12, 5), 3);
}

std::vector<Position> BoardConfiguration::getSoldiersBPositions()
{
	if (_boardInitOptions == BoardInitOptions::FromFile)
		return _soldierAPositions;
	else
		return selectFreePositions(Position(0, 8), Position(12, 12), 3);
}

void BoardConfiguration::generateRandomPositions() {
	if (rand() % 2 == 0) {
		randomCells(_seaPositions, Position(7, 3), Position(11, 9), 0.5);
		randomCells(_forestPositions, Position(1, 3), Position(7, 9), 0.5);
	}
	else {
		randomCells(_forestPositions, Position(7, 3), Position(11, 9), 0.5);
		randomCells(_seaPositions, Position(1, 3), Position(7, 9), 0.5);
	}

	_flagBPosition = selectCells(Position(0, 11), Position(12, 12), 1).front();
	_flagAPosition = selectCells(Position(0, 0), Position(12, 1), 1).front();
}

int BoardConfiguration::loadPositionsFromFile(string inputFile)
{
	// go over input file
	// push relevat positions to vectors:
	// forestPosition, seaPosition, flagA,
	// flagB, SoldierAPositions, SoldierBPos
	// (;
	// Hint:: use split from Utils.h
	// if any error return !0
	return 0;
}

Position randomPosition(const Position& UpperLeft, const Position& BottomRight) {
	int minX = UpperLeft.getX(), minY = UpperLeft.getY(),
		maxX = BottomRight.getX(), maxY = BottomRight.getY();
	int rx = minX + (rand() % (int)(maxX - minX + 1));
	int ry = minY + (rand() % (int)(maxY - minY + 1));

	return Position(rx, ry);
}
std::vector<Position> BoardConfiguration::selectFreePositions(Position UpperLeft, Position BottomRight, int num)
{
	vector<Position> positions = vector<Position>();
	while (num) {
		Position pos;
		do {
			pos = randomPosition(UpperLeft, BottomRight);
		} while (find(positions.begin(), positions.end(), pos) != positions.end() ||
			find(_seaPositions.begin(), _seaPositions.end(), pos) != _seaPositions.end() ||
			find(_forestPositions.begin(), _forestPositions.end(), pos) != _forestPositions.end() ||
			_flagAPosition == pos || _flagBPosition == pos);
		positions.push_back(pos);
		--num;
	}
	return positions;
}

vector<Position> selectCells(const Position UpperLeft, const Position BottomRight, int numToSelect)
{
	std::vector<Position> positions = vector<Position>();
	while (numToSelect) {
		Position pos;
		do {
			pos = randomPosition(UpperLeft, BottomRight);
		} while (std::find(positions.begin(), positions.end(), pos) != positions.end());
		positions.push_back(pos);
		--numToSelect;
	}
	return positions;
}

void randomCells(vector<Position>& positions, const Position UpperLeft, const Position BottomRight, const double prob)
{
	for (auto i = UpperLeft.getX(); i <= BottomRight.getX(); ++i)
	{
		for (auto j = UpperLeft.getY(); j <= BottomRight.getY(); ++j)
		{
			double r = ((double)rand()) / RAND_MAX;
			r = r < 0 ? -r : r;
			if (r < prob) {
				positions.push_back(Position(i, j));
			}
		}
	}
}