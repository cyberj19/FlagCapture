#pragma once
#include <iostream>
#include <fstream>
#include "Position.h"
#include "GameSettings.h"
#include "enums.h"
#include "GameBoard.h"
#include <string>
#include <vector>
#include <map>

void randomCells(std::vector<Position>& positions, Position UpperLeft, Position BottomRight, double prob);
std::vector<Position> selectCells(Position UpperLeft, Position BottomRight, int num);
const int maxCharPerLine = 1000;

class BoardConfiguration {
	BoardInitOptions _boardInitOptions;  //FromFile, Randomized 

	std::vector<Position> _seaPositions;
	std::vector<Position> _forestPositions;

	Position _flagAPosition;
	Position _flagBPosition;

	std::vector<Position> _soldierAPositions;
	std::vector<Position> _soldierBPositions;

	std::vector<std::string> _errors;
	std::map<char, int> _toolsValidation;
	std::map<char, int> _illegalChars;

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

	void loadPositionsFromFile(std::string inputFile);
	void initializeValidationMaps();
	std::string readLineFromFile(std::ifstream &file);
	void updatePositions(std::string line, int row);
	void updateErrorMessagesVec(std::string fileName);

	std::vector<Position> selectFreePositions(Position UpperLeft, Position BottomRight, int num);
};