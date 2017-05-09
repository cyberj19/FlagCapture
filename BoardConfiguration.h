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

	std::vector<std::string> loadPositionsFromFile(std::string inputFile);
	void initializeValidationToolsMap(std::map<char, int>& validationToolsMap);
	std::string readLineFromFile(std::ifstream &file);
	int updatePositions(std::string line, std::map<char, int>& wrongCharsMap, std::map<char, int>& validationToolsMap);
	void updateErrorMessagesVec(std::map<char, int> wrongCharsMap, std::map<char, int> validationToolsMap, std::vector<std::string>& errorMessages, std::string fileName);

	std::vector<Position> selectFreePositions(Position UpperLeft, Position BottomRight, int num);
};