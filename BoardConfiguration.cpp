#include "BoardConfiguration.h"
#include <time.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

BoardConfiguration::BoardConfiguration()
	: _errors(), _toolsValidation(), _illegalChars(), _soldierAPositions(),
		_soldierBPositions(), _seaPositions(), _forestPositions()
{}

int BoardConfiguration::loadSettings(GameSettings settings)
{
	_boardInitOptions = settings.getBoardInitOptions();
	_errors.clear();
	if (_boardInitOptions == BoardInitOptions::FromFile)
		loadPositionsFromFile(settings.getBoardInputFilePath());
	else
		generateRandomPositions();
	return _errors.size() == 0;
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


void BoardConfiguration::loadPositionsFromFile(std::string inputFile) {
	ifstream file(inputFile);    //open file for reading
	if (!file.is_open()) {
		_errors.push_back("Error opening file: " + inputFile);
		return;
	}

	bool ifFinished = true;
	initializeValidationMaps();

	int rowCount = 0;
	while (rowCount < ROWS) {
		string line = readLineFromFile(file);
		if (line == "") {
			_errors.push_back("Not enough rows in board: " + inputFile);
			break;
		}
		updatePositions(line, rowCount++);
	}
	updateErrorMessagesVec(inputFile);
	file.close();
}

void BoardConfiguration::initializeValidationMaps() {
	_illegalChars.clear();
	_toolsValidation.clear();
	for (char ch = '1'; ch <= '3'; ch++) _toolsValidation[ch] = 0;
	for (char ch = '7'; ch <= '9'; ch++) _toolsValidation[ch] = 0;
	_toolsValidation['A'] = 0;
	_toolsValidation['B'] = 0;
}

string formatToolErrorMessage(char tool, string fileName) {
	string error = "Wrong settings for player ";
	error += (tool >= '1' && tool <= '3') || tool == 'A' ? 'A' : 'B';
	error += " tools in file " + fileName;
	return error;
}

string formatIllegalCharErrorMessage(char ch, string fileName) {
	string error = "Wrong character on board: " + string(1, ch);
	error += " in file " + fileName + "\n";
	return error;
}

void BoardConfiguration::updateErrorMessagesVec(string fileName) {
	
	for (auto &k : _toolsValidation) {
		if (k.second != 1)
			_errors.push_back(formatToolErrorMessage(k.first, fileName));
	}

	for (auto& k : _illegalChars) {
		if (k.second == 1)
			_errors.push_back(formatIllegalCharErrorMessage(k.first, fileName));
	}
}

void BoardConfiguration::updatePositions(string line, int row) {
	int numCols = line.size();

	if (numCols != COLS) {
		//error
	}
	for (int col = 0; col < numCols; ++col) {
		char ch = line[col];

		if (ch >= '1' && ch <= '3') {
			_toolsValidation[ch]++;
			_soldierAPositions[ch - '1'] = Position(row, col);
		}
		else if (ch >= '7' && ch <= '9') {
			_toolsValidation[ch]++;
			_soldierBPositions[ch - '7'] = Position(row, col);
		}
		else if (ch == 'A') {
			_toolsValidation[ch]++;
			_flagAPosition = Position(row, col);
		}
		else if (ch == 'B') {
			_toolsValidation[ch]++;
			_flagBPosition = Position(row, col);
		}
		else if (ch == 'S') {
			_seaPositions.push_back(Position(row, col));
		}
		else if (ch == 'T') {
			_forestPositions.push_back(Position(row, col));
		}
		else {
			if (_illegalChars.count(ch) == 0)
				_illegalChars.insert(pair<char, int>(ch, 0));
			_illegalChars[ch]++;
		}
	}
}

string trim(string str) {

	size_t endpos = str.find_last_not_of(" \t\r\n");
	if (string::npos != endpos)
	{
		str = str.substr(0, endpos + 1);
	}

	size_t startpos = str.find_first_not_of(" \t\r\n");
	if (string::npos != startpos)
	{
		str = str.substr(startpos);
	}

	return str;
}
string BoardConfiguration::readLineFromFile(ifstream &file) {
	string line = "";
	if (file.eof()) return line;
	do {
		file >> line;
		line = trim(line);
	} while (line == string("") && !file.eof());
	if (file.eof()) return string("");

	size_t commentChar = line.find_first_of("#", 0);
	line = line.substr(0, commentChar);
	line = trim(line);
	return line;
	/*
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
	return str;*/
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