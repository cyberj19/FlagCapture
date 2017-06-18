#include "BoardConfiguration.h"
#include <time.h>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <sstream>
#include "Board.h"
using namespace std;

BoardConfiguration::BoardConfiguration()
	: _errors(), _toolsValidation(), _illegalChars(), _soldierAPositions(),
		_soldierBPositions(), _seaPositions(), _forestPositions()
{}

int BoardConfiguration::loadSettings(GameSettings settings) {
	_boardInitOptions = settings.getBoardInitOptions();
	_errors.clear();
	if (_boardInitOptions == BoardOptions::FromFile)
		loadPositionsFromFile(settings.getBoardInputFilePath());
	else
		generateRandomPositions();
	return _errors.size() == 0;
}

vector<Pos203398664> BoardConfiguration::getSoldiersAPositions() const{
	return _soldierAPositions;
}

vector<Pos203398664> BoardConfiguration::getSoldiersBPositions() const{
	return _soldierBPositions;
}

string emptyBoardString() {
	stringstream board;
	for (int r = 0; r < Board::Rows; r++) {
		for (int c = 0; c < Board::Cols; c++)
			board << " ";
		board << "\n";
	}
	return board.str();
}
void setCharsInBoardString(string &boardString, const vector<Pos203398664>& positions, const char ch) {
	for (const Pos203398664& pos : positions)
		boardString[pos.getY()*(Board::Rows + 1) + pos.getX()] = ch;
}
void setCharsInBoardString(string &boardString, Pos203398664 pos, const char ch) {
	boardString[pos.getY()*(Board::Rows + 1) + pos.getX()] = ch;
}
void setNumsInBoardString(string &boardString, const vector<Pos203398664>& positions, int seed) {
	for (const Pos203398664& pos : positions)
		boardString[pos.getY()*(Board::Rows + 1) + pos.getX()] = '0' + (seed++);
}

string BoardConfiguration::getBoardString() const{
	string boardString = emptyBoardString();
	setCharsInBoardString(boardString, _seaPositions, 'S');
	setCharsInBoardString(boardString, _forestPositions, 'T');
	setNumsInBoardString(boardString, _soldierAPositions, 1);
	setNumsInBoardString(boardString, _soldierBPositions, 7);
	setCharsInBoardString(boardString, _flagAPosition, 'A');
	setCharsInBoardString(boardString, _flagBPosition, 'B');

	return boardString;
}

void BoardConfiguration::randomizeTeamsPositions(){
	_flagBPosition = selectFreePositions(Pos203398664(0, 11), Pos203398664(12, 12), 1).front();
	_flagAPosition = selectFreePositions(Pos203398664(0, 0), Pos203398664(12, 1), 1).front();
	_soldierAPositions = selectFreePositions(Pos203398664(0, 0), Pos203398664(12, 5), 3);
	_soldierBPositions = selectFreePositions(Pos203398664(0, 8), Pos203398664(12, 12), 3);

}

void BoardConfiguration::generateRandomPositions() {
	// switch sides of forest and sea randomly
	if (rand() % 2 == 0) {
		randomCells(_seaPositions, Pos203398664(7, 3), Pos203398664(11, 9), 0.5);
		randomCells(_forestPositions, Pos203398664(1, 3), Pos203398664(7, 9), 0.5);
	}
	else {
		randomCells(_forestPositions, Pos203398664(7, 3), Pos203398664(11, 9), 0.5);
		randomCells(_seaPositions, Pos203398664(1, 3), Pos203398664(7, 9), 0.5);
	}
}


void BoardConfiguration::loadPositionsFromFile(std::string inputFile) {
	ifstream file(inputFile);
	if (!file.is_open()) {
		_errors.push_back("Error opening file: " + inputFile);
		return;
	}

	bool ifFinished = true;
	initializeValidationMaps();
	initializePositionVectors();
	
	for (int rowCount = 0; rowCount < Board::Rows; rowCount++) {
		string line = readLineFromFile(file);
		if (line == "#") break; // # indicates eof in our function
		updatePositions(line, rowCount);
	}	
	
	generateErrors(inputFile);
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

void BoardConfiguration::initializePositionVectors()
{
	_forestPositions = vector<Pos203398664>();
	_seaPositions = vector<Pos203398664>();

	_soldierAPositions = vector<Pos203398664>(3);
	_soldierBPositions = vector<Pos203398664>(3);
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

void BoardConfiguration::generateErrors(string fileName) {
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
	for (int col = 0; col < (int) line.size(); ++col) {
		char ch = line[col];
		Pos203398664 currentPosition = Pos203398664(col, row);
		if (ch >= '1' && ch <= '3') {
			_toolsValidation[ch]++;
			_soldierAPositions[ch - '1'] = currentPosition;
		}
		else if (ch >= '7' && ch <= '9') {
			_toolsValidation[ch]++;
			_soldierBPositions[ch - '7'] = currentPosition;
		}
		else if (ch == 'A') {
			_toolsValidation[ch]++;
			_flagAPosition = currentPosition;
		}
		else if (ch == 'B') {
			_toolsValidation[ch]++;
			_flagBPosition = currentPosition;
		}
		else if (ch == 'S') {
			_seaPositions.push_back(currentPosition);
		}
		else if (ch == 'T') {
			_forestPositions.push_back(currentPosition);
		}
		else if (ch != ' ') {
			if (_illegalChars.count(ch) == 0)
				_illegalChars.insert(pair<char, int>(ch, 0));
			_illegalChars[ch]++;
		}
	}
}


void removeComment(string &str) {
	size_t commentChar = str.find_first_of("#", 0);
	str = str.substr(0, commentChar);
}

void limitSize(string &str, int numChars) {
	if (numChars > (int) str.size()) 
		str = str.substr(0, numChars);
}
string BoardConfiguration::readLineFromFile(ifstream &file) {
	string line = "#";
	if (file.eof()) return line;

	getline(file, line);
	removeComment(line);
	limitSize(line, Board::Cols);
	return line;
}

Pos203398664 randomPosition(const Pos203398664& UpperLeft, const Pos203398664& BottomRight) {
	int minX = UpperLeft.getX(), minY = UpperLeft.getY(),
		maxX = BottomRight.getX(), maxY = BottomRight.getY();
	int rx = minX + (rand() % (int)(maxX - minX + 1));
	int ry = minY + (rand() % (int)(maxY - minY + 1));

	return Pos203398664(rx, ry);
}
std::vector<Pos203398664> BoardConfiguration::selectFreePositions(Pos203398664 UpperLeft, 
	Pos203398664 BottomRight, int num)
{
	vector<Pos203398664> positions = vector<Pos203398664>();
	while (num) {
		Pos203398664 pos;
		do {
			pos = randomPosition(UpperLeft, BottomRight);
		} 
		//check if pos is already contained in selected positions, or in 
		// forest or in sea, or occupied by flags
		while (find(positions.begin(), positions.end(), pos) != positions.end() ||
			find(_seaPositions.begin(), _seaPositions.end(), pos) != _seaPositions.end() ||
			find(_forestPositions.begin(), _forestPositions.end(), pos) != _forestPositions.end() ||
			_flagAPosition == pos || _flagBPosition == pos);
		positions.push_back(pos);
		--num;
	}
	return positions;
}


void randomCells(vector<Pos203398664>& positions, const Pos203398664 UpperLeft, const Pos203398664 BottomRight, const double prob)
{
	for (int i = UpperLeft.getX(); i <= BottomRight.getX(); ++i) {
		for (int j = UpperLeft.getY(); j <= BottomRight.getY(); ++j){
			double r = ((double)rand()) / RAND_MAX;
			if (abs(r) < prob) {
				positions.push_back(Pos203398664(i, j));
			}
		}
	}
}