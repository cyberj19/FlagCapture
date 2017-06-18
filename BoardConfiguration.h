#pragma once
#include <iostream>
#include <fstream>
#include "Pos203398664.h"
#include "GameSettings.h"
#include "enums.h"
#include <string>
#include <vector>
#include <map>

void randomCells(std::vector<Pos203398664>& positions, 
	Pos203398664 UpperLeft, Pos203398664 BottomRight, double prob);

class BoardConfiguration {
	BoardOptions _boardInitOptions;  //FromFile, Randomized 

	std::vector<Pos203398664> _seaPositions;
	std::vector<Pos203398664> _forestPositions;

	Pos203398664 _flagAPosition;
	Pos203398664 _flagBPosition;

	std::vector<Pos203398664> _soldierAPositions;
	std::vector<Pos203398664> _soldierBPositions;

	std::vector<std::string> _errors;
	std::map<char, int> _toolsValidation;
	std::map<char, int> _illegalChars;

public:
	BoardConfiguration();
	
	int loadSettings(GameSettings settings);

	std::vector<Pos203398664> getSeaPositions() const { return _seaPositions; }
	std::vector<Pos203398664> getForestPositions() const { return _forestPositions; }

	std::vector<Pos203398664> getSoldiersAPositions() const;
	std::vector<Pos203398664> getSoldiersBPositions() const;

	Pos203398664 getFlagAPosition() const { return _flagAPosition; }
	Pos203398664 getFlagBPosition() const { return _flagBPosition; }

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

	std::vector<Pos203398664> selectFreePositions(Pos203398664 UpperLeft, Pos203398664 BottomRight, int num);
};