#include "BoardConfiguration.h"
#include <vector>
#include <time.h>
using namespace std;

BoardConfiguration::BoardConfiguration(GameSettings settings, GameBoard &board)
	: _boardInitOptions(settings.getBoardInitOptions()),
	  _board(board)
{
	srand(time(NULL));
	if (_boardInitOptions == BoardInitOptions::FromFile) {
		//loadPositionsFromFile();
		// load file from 
		// settings.getBoardInputFilePath()
	}
	else
		generateRandomPositions();
}

std::vector<Position> BoardConfiguration::getSoldiersAPositions() const
{
	if (_boardInitOptions == BoardInitOptions::FromFile)
		return _soldierAPositions;
	else
		return selectCells(Position(0, 0), Position(12, 5), _board, 3);
}

std::vector<Position> BoardConfiguration::getSoldiersBPositions() const
{
	if (_boardInitOptions == BoardInitOptions::FromFile)
		return _soldierAPositions;
	else
		return selectCells(Position(0, 8), Position(12, 12), _board, 3);
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

void BoardConfiguration::loadPositionsFromFile()
{
}

Position randomPosition(const Position& UpperLeft, const Position& BottomRight) {
	int minX = UpperLeft.getX(), minY = UpperLeft.getY(),
		maxX = BottomRight.getX(), maxY = BottomRight.getY();
	int rx = minX + (rand() % (int)(maxX - minX + 1));
	int ry = minY + (rand() % (int)(maxY - minY + 1));

	return Position(rx, ry);
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

vector<Position> selectCells(Position UpperLeft, Position BottomRight, GameBoard board, int numToSelect)
{
	vector<Position> positions = vector<Position>();
	while (numToSelect) {
		Position pos;
		do {
			pos = randomPosition(UpperLeft, BottomRight);
		} while (find(positions.begin(), positions.end(), pos) != positions.end() ||
			board[pos.getY()][pos.getX()].getType() != CellType::EMPTY);
		positions.push_back(pos);
		--numToSelect;
	}
	return positions;
}

vector<Position> selectPredicateCells(Position UpperLeft, Position BottomRight, int numToSelect,
	bool(*predicate)(Position pos) = [](Position pos) {return true; }) {
	vector<Position> positions = vector<Position>();
	while (numToSelect) {
		Position pos;
		do {
			pos = randomPosition(UpperLeft, BottomRight);
		} while (find(positions.begin(), positions.end(), pos) != positions.end() || !predicate(pos));
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