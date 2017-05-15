#pragma once
#include <iostream>
#include <fstream>
#include "Position.h"
#include "GameSettings.h"
#include "enums.h"
#include <string>
#include <vector>
#include <map>

void randomCells(std::vector<Position>& positions, 
	Position UpperLeft, Position BottomRight, double prob);

class BoardConfiguration {
	BoardOptions _boardInitOptions;  //FromFile, Randomized 

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

	std::vector<Position> getSoldiersAPositions() const;
	std::vector<Position> getSoldiersBPositions() const;

	Position getFlagAPosition() const { return _flagAPosition; }
	Position getFlagBPosition() const { return _flagBPosition; }

	std::string getBoardString() const;
	std::vector<std::string> getErrors() const { return _errors; }

	void randomizeTeamsPositions();
private:
	void generateRandomPositions();

	void loadPositionsFromFile(std::string inputFile);
	void initializeValidationMaps();
	void initializePositionVectors();
	std::string readLineFromFile(std::ifstream &file);
	void updatePositions(std::string line, int row);
	void generateErrors(std::string fileName);

	std::vector<Position> selectFreePositions(Position UpperLeft, Position BottomRight, int num);
};