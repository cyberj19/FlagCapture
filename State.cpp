#include "State.h"
#include "Soldier.h"
#include <time.h>


void State::step()
{
	clock++;
	for (Soldier* soldier : soldiersA) {
		soldier->step();
	}
	
	for (Soldier* soldier : soldiersB) {
		soldier->step();
	}
}

void State::reset() 
{
	clock = 0;
	isFinished = false;
	stepsBuffer.clear();
	
	
	if (_settings.getBoardOptions() != BoardInitOptions::FromFile)
	{
		soldierAPositions = selectCells(Position(0, 0), Position(12, 5), board, 3);
		soldierBPositions = selectCells(Position(0, 8), Position(12, 12), board, 3);
	}

	initSoldiers();
}

void State::control(Input input)
{
	for (Soldier* soldier : soldiersA) {
		soldier->control(input);
	}

	for (Soldier* soldier : soldiersB) {
		soldier->control(input);
	}
}

void State::updateBoardSoldierMoved(Position source, Position dest)
{
	if (source.x == dest.x && source.y == dest.y) return;
	board[dest.x][dest.y].setSoldier(board[source.x][source.y].getSoldier());
	boardChanges[0] = dest;
	board[source.x][source.y].unsetSoldier();
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
	//lastStep.clear();
	char *newStep = new char[6];
	char dir;
	if (dirX == 1) dir = 'R';
	else if (dirX == -1) dir = 'L';
	else if (dirY == 1) dir = 'U';
	else if (dirY == -1) dir = 'D';
	sprintf(newStep, "%d,%d,%c\n", clock, soldierId, dir);
	stepsBuffer += newStep;
}
void State::updateBoardSoldierDied(Position placeOfDeath)
{
	board[placeOfDeath.x][placeOfDeath.y].unsetSoldier();
	boardChanges[0] = placeOfDeath;
	boardChanges[1] = placeOfDeath;
}


void State::initSoldiers() {
	srand(time(NULL));
	soldiersA = std::vector<Soldier*>();
	addSoldiers(soldiersA, Player::A, soldierAPositions);
	soldierCounterA = soldiersA.size();

	soldiersB = std::vector<Soldier*>();
	addSoldiers(soldiersB, Player::B, soldierBPositions);
	soldierCounterB = soldiersB.size();
}
void State::addSoldiers(std::vector<Soldier*>& soldiersVector, Player player,
	std::vector<Position> positions) {
	for (int s = 0; s < 3; ++s) {
		Soldier *soldier = new Soldier(player, SoldierType(s), this, positions[s]);
		soldiersVector.push_back(soldier);
		board[positions[s].y][positions[s].x].setSoldier(soldier);
	}
}
void State::initBoard() 
{
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			board[i][j] = Cell();

	board[flagAPosition.y][flagAPosition.x].setType(CellType::FLAG_A);
	board[flagBPosition.y][flagBPosition.x].setType(CellType::FLAG_B);
	fillCells(seaPositions, CellType::SEA);
	fillCells(forestPositions, CellType::FOREST);
	
}

void State::fillCells(const std::vector<Position>& positions, CellType type) {
	for (auto& pos : positions) {
		board[pos.y][pos.x].setType(type);
	}
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

std::vector<Position> selectCells(const Position UpperLeft, const Position BottomRight, int numToSelect)
{
	std::vector<Position> positions = vector<Position>();
	int minX = UpperLeft.x, minY = UpperLeft.y, 
		maxX = BottomRight.x, maxY = BottomRight.y;
	while (numToSelect) {
		Position pos;
		do {
			pos = Position(minX + (rand() % (int)(maxX - minX + 1), 
									minY + (rand() % (int)(maxY - minY + 1))));
			
		} while (std::find(positions.begin(), positions.end(), pos) != positions.end());
		positions.push_back(pos);
		--numToSelect;
	}
	return positions;
}

vector<Position> selectCells(Position UpperLeft, Position BottomRight, GameBoard board, int numToSelect)
{
	vector<Position>& positions = vector<Position>();
	int minX = UpperLeft.x, minY = UpperLeft.y,
		maxX = BottomRight.x, maxY = BottomRight.y;
	while (numToSelect) {
		Position pos;
		do {
			pos = Position(minX + (rand() % (int)(maxX - minX + 1),
				minY + (rand() % (int)(maxY - minY + 1))));
		} while (std::find(positions.begin(), positions.end(), pos) != positions.end() ||
			board[pos.y][pos.x].getType() != CellType::EMPTY);
		positions.push_back(pos);
		--numToSelect;
	}
	return positions;
}