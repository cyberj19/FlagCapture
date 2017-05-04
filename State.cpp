#include "State.h"
#include "Soldier.h"
#include <time.h>
using namespace std;

State::State(GameSettings settings)
	: _settings(settings), forestPositions(), seaPositions() {
	// do something with settings;
	srand(time(NULL));

	if (_settings.isRecording()) {
		stepsBufferA = string();
		stepsBufferB = string();
	}

	if (_settings.getBoardOptions() == BoardInitOptions::FromFile) {
		// load file from 
		// settings.getBoardFilePath()
	}
	else {
		randomCells(seaPositions, Position(7, 3), Position(11, 9), 0.5);
		randomCells(forestPositions, Position(1, 3), Position(6, 9), 0.5);
		flagBPosition = selectCells(Position(0, 11), Position(12, 12), 1).front();
		flagAPosition = selectCells(Position(0, 0), Position(12, 1), 1).front();
	}

	initBoard();
	reset();
}

void State::initBoard()
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			board[i][j] = Cell();

	getCell(flagAPosition).setType(CellType::FLAG_A);
	getCell(flagBPosition).setType(CellType::FLAG_B);
	fillCells(seaPositions, CellType::SEA);
	fillCells(forestPositions, CellType::FOREST);
}

void State::reset()
{
	clock = 0;
	isFinished = false;
	stepsBufferA.clear();
	stepsBufferB.clear();

	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			board[i][j].unsetSoldier();

	if (_settings.getBoardOptions() != BoardInitOptions::FromFile)
	{
		soldierAPositions = selectCells(Position(0, 0), Position(12, 5), board, 3);
		soldierBPositions = selectCells(Position(0, 8), Position(12, 12), board, 3);
	}

	initSoldiers();
}

void State::initSoldiers() {
	soldiersA = vector<Soldier>();
	addSoldiers(soldiersA, Player::A, soldierAPositions);
	soldierCounterA = soldiersA.size();

	soldiersB = vector<Soldier>();
	addSoldiers(soldiersB, Player::B, soldierBPositions);
	soldierCounterB = soldiersB.size();
}

void State::addSoldiers(vector<Soldier>& soldiersVector, Player player, vector<Position> positions) {
	for (int s = 0; s < 3; ++s) {
		Soldier soldier = Soldier(this, player, SoldierType(s), positions[s]);
		soldiersVector.push_back(soldier);
	}

	for (int s = 0; s < 3; s++)
		getCell(positions[s]).setSoldier(&soldiersVector[s]);
}

void State::step()
{
	clock++;
	for (auto& soldier : soldiersA) {
		soldier.step();
	}
	
	for (auto& soldier : soldiersB) {
		soldier.step();
	}
}

void State::control(Input input)
{
	for (auto& soldier : soldiersA) {
		soldier.control(input);
	}

	for (auto& soldier : soldiersB) {
		soldier.control(input);
	}
}

void State::updateBoardSoldierMoved(Position source, Position dest)
{
	if (source.x == dest.x && source.y == dest.y) return;
	getCell(dest).setSoldier(getCell(source).getSoldier());
	boardChanges[0] = dest;
	getCell(source).unsetSoldier();
	boardChanges[1] = source;
}

void State::notifySoldierDied(Soldier *soldier) {
	updateBoardSoldierDied(soldier->getCurrentPosition());

	if (soldier->getPlayer() == Player::A) {
		soldierCounterA--;
		if (soldierCounterA == 0) {
			isFinished = true;
			winner = Player::B;
		}
	}
	else if (soldier->getPlayer() == Player::B) {
		soldierCounterB--;
		if (soldierCounterB == 0) {
			isFinished = true;
			winner = Player::A;
		}
	}
}
void State::updateLastStep(int soldierId, int dirX, int dirY)
{
	if (!_settings.isRecording()) return;

	char *newStep = new  char[6];
	char dir;
	if (dirX == 1) dir = 'R';
	else if (dirX == -1) dir = 'L';
	else if (dirY == 1) dir = 'D';
	else if (dirY == -1) dir = 'U';
	sprintf(newStep, "%d,%d,%c\n", clock, soldierId, dir);

	if (soldierId <= 3)
		stepsBufferA += newStep;
	else
		stepsBufferB += newStep;
}
void State::updateBoardSoldierDied(Position placeOfDeath)
{
	getCell(placeOfDeath).unsetSoldier();
	boardChanges[0] = placeOfDeath;
	boardChanges[1] = placeOfDeath;
}


void State::fillCells(const std::vector<Position>& positions, CellType type) {
	for (auto& pos : positions) {
		getCell(pos).setType(type);
	}
}

string State::getStepBuffer(Player player) {
	if (player == Player::A)
		return stepsBufferA;
	else
		return stepsBufferB;
}

void randomCells(vector<Position>& positions, const Position UpperLeft, const Position BottomRight, const double prob)
{
	for (auto i = UpperLeft.x; i < BottomRight.x; ++i)
	{
		for (auto j = UpperLeft.y; j < BottomRight.y; ++j)
		{
			double r = ((double)rand()) / RAND_MAX;
			r = r < 0 ? -r : r;
			if( r < prob) {
				positions.push_back(Position(i, j));
			}
		}
	}
}

vector<Position> selectCells(const Position UpperLeft, const Position BottomRight, int numToSelect)
{
	std::vector<Position> positions = vector<Position>();
	int minX = UpperLeft.x, minY = UpperLeft.y, 
		maxX = BottomRight.x, maxY = BottomRight.y;
	while (numToSelect) {
		Position pos;
		do {
			int rx = minX + (rand() % (int)(maxX - minX + 1));
			int ry = minY + (rand() % (int)(maxY - minY + 1));
			pos = Position(rx, ry);
		} while (std::find(positions.begin(), positions.end(), pos) != positions.end());
		positions.push_back(pos);
		--numToSelect;
	}
	return positions;
}

vector<Position> selectCells(Position UpperLeft, Position BottomRight, GameBoard board, int numToSelect)
{
	vector<Position> positions = vector<Position>();
	int minX = UpperLeft.x, minY = UpperLeft.y,
		maxX = BottomRight.x, maxY = BottomRight.y;
	while (numToSelect) {
		Position pos;
		do {
			int rx = minX + (rand() % (int)(maxX - minX + 1));
			int ry = minY + (rand() % (int)(maxY - minY + 1));
			pos = Position(rx, ry);
		} while (find(positions.begin(), positions.end(), pos) != positions.end() ||
			board[pos.y][pos.x].getType() != CellType::EMPTY);
		positions.push_back(pos);
		--numToSelect;
	}
	return positions;
}