#include "BoardConfiguration.h"
#include <time.h>


using namespace std;

BoardConfiguration::BoardConfiguration() {}

int BoardConfiguration::loadSettings(GameSettings settings)
{
	_boardInitOptions = settings.getBoardInitOptions();
	if (_boardInitOptions == BoardInitOptions::FromFile)
		return  0;//loadPositionsFromFile(settings.getBoardInputFilePath());
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


std::vector<std::string> BoardConfiguration::loadPositionsFromFile(std::string inputFile) {

	vector<string> errorMessages;      // errorMessages.size() == 0

	ifstream file(inputFile);    //open file for reading
	if (!file.is_open()) {
		errorMessages.push_back("Error opening file: " + inputFile);
		return errorMessages;
	}

	bool ifFinished = true;
	map<char, int> wrongCharsMap;   //such as:  4,5,C,J,^,&, etc.
	map<char, int> validationToolsMap;  //settings validation for players A, B
	initializeValidationToolsMap(validationToolsMap);

	string line = readLineFromFile(file);   //read a whole line until \n or \r\n  or EOF
	while (!file.eof() && ifFinished) {
		if (updatePositions(line, wrongCharsMap, validationToolsMap) <= ROWS) {      //read 13 lines
			string line = readLineFromFile(file);
		}
		else {
			ifFinished = false;
		}
	}
	
	updateErrorMessagesVec(wrongCharsMap, validationToolsMap, errorMessages, inputFile);

	if (errorMessages.size()) {
		return errorMessages;
	}
	errorMessages.push_back("No errors, file is valid");
	return errorMessages;
}

void BoardConfiguration::initializeValidationToolsMap(map<char, int>& validationToolsMap) {
	//wrong tools A
	validationToolsMap['1'] = 0;
	validationToolsMap['2'] = 0;
	validationToolsMap['3'] = 0;
	validationToolsMap['A'] = 0;
	//wrong tools B
	validationToolsMap['7'] = 0;
	validationToolsMap['8'] = 0;
	validationToolsMap['9'] = 0;
	validationToolsMap['B'] = 0;

}

void BoardConfiguration::updateErrorMessagesVec(map<char, int> wrongCharsMap, map<char, int> validationToolsMap, vector<string>& errorMessages, string fileName) {
	
	for (auto &k : validationToolsMap) {
		if (k.second != 1) {  //if 0 or greater than 1  -  wrong tool
			if ((k.first >= '1' && k.first <= '3') || k.first == 'A') {
				errorMessages.push_back("Wrong settings for player A tools in file " + fileName + "\n");
				
			}
			else {
				errorMessages.push_back("Wrong settings for player B tools in file " + fileName + "\n");
			}
		}
	}

	for (auto& k : wrongCharsMap) {
		if (k.second == 1) {
			string error = "Wrong character on board: " + string(1, k.first);
			error += " in file " + fileName + "\n";
			errorMessages.push_back(error);
		}
	}
}

int BoardConfiguration::updatePositions(string line, map<char, int>& wrongCharsMap, map<char, int>& validationToolsMap) {

	static int rowIndex = 0;    //read only 13 first rows
	int colIndex = 0;

	                                                                  //read first 13 characters
	for (std::string::iterator it = line.begin(); it != line.end() && colIndex < COLS; ++it) {

		if (*it >= '1' && *it <= '3') {
			validationToolsMap[*it]++;
			_soldierAPositions.push_back(Position(rowIndex, colIndex));
		}
		else if (*it >= '7' && *it <= '9') {
			validationToolsMap[*it]++;
			_soldierBPositions.push_back(Position(rowIndex, colIndex));
		}
		else if (*it == 'A') {
			validationToolsMap[*it]++;
			_flagAPosition = (rowIndex, colIndex);
		}
		else if (*it == 'B') {
			validationToolsMap[*it]++;
			_flagBPosition = (rowIndex, colIndex);
		}
		else if (*it == 'S') {
			_seaPositions.push_back(Position(rowIndex, colIndex));
		}
		else if (*it == 'T') {
			_forestPositions.push_back(Position(rowIndex, colIndex));
		}
		else {
			//wrong char
			if (!wrongCharsMap[*it]) {   //only if the char hasn't shown yet
				wrongCharsMap[*it]++;     //count char frequency
			}
		}
		colIndex++;
	}
	rowIndex++;
	return rowIndex;
}

string BoardConfiguration::readLineFromFile(ifstream &file) {
	//read line from text file until   '\r\n'  || '\n'  only

	string str = "";
	char ch, prevCh = ' ';

	file.get(ch);
	while (ch != EOF && str.size() <= maxCharPerLine) {
		//if prev == '\r' && ch == '\n'  :: we don't want '\r' to get into the string
		//if prev == '\r' && ch !== '\n' :: later while checking the board  - an error will be printed  - wrong character
		if (prevCh == '\r' && ch == '\n') {  //end of line
			str.erase(str.end() - 1);
			return str;
		}
		else if (ch == '\n') {  //end of line
			return str;
		}
		str += ch;
		prevCh = ch;
		file.get(ch);
	}
	return str;
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