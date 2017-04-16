#include "State.h"
#include "Soldier.h"
#include <time.h>


const int State::forest_positions[22] = { 6,0,   7,0,     6,1,    3,2,    4,2,    5,2,    6,2,     5,3,    6,3,    7,3,     8,3 };
const int State::forest_size = 11;
const int State::sea_positions[28] = { 5,7,   4,8,    5,8,    3,9,   4,9,   5,9,   6,9,   7,9,   8,9,   9,9,  6,10,   7,10,   8,10,   7,11 };
const int State::sea_size = 14;
const int State::flgAPos[2] = { 0,10 };
const int State::flgBPos[2] = { 12,1 };


void State::initVectorFreePositions(std::vector<Position>& freePositions, int rowStart, int rowEnd)
{
	freePositions = std::vector<Position>();
	for (int i = rowStart; i < rowEnd; i++) {
		for (int j = 0; j < COLS; j++) {
			if (board[i][j].getType() == CellType::EMPTY)
				freePositions.push_back(Position(i, j));
		}
	}
}

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
	initBoard();
	initVectorFreePositions(freePositionsA, 0, 5);
	initVectorFreePositions(freePositionsB, 8, 13);
	soldiersFactory();
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
void State::updateBoardSoldierDied(Position placeOfDeath)
{
	board[placeOfDeath.x][placeOfDeath.y].unsetSoldier();
	boardChanges[0] = placeOfDeath;
	boardChanges[1] = placeOfDeath;
}

void State::initBoardPosition(Soldier* soldier) {
	Player player = soldier->getPlayer();
	std::vector<Position>& freePositions = player == Player::A ? freePositionsA : freePositionsB;
	int randomIndex = rand() % freePositions.size();
	soldier->setCurrentPosition(freePositions[randomIndex].x, freePositions[randomIndex].y);
	board[freePositions[randomIndex].x][freePositions[randomIndex].y].setSoldier(soldier);
	freePositions.erase(freePositions.begin() + randomIndex);
}


void State::soldiersFactory() {
	srand(time(NULL));
	soldiersA = std::vector<Soldier*>();
	addSoldiers(soldiersA, Player::A);
	soldierCounterA = soldiersA.size();

	soldiersB = std::vector<Soldier*>();
	addSoldiers(soldiersB, Player::B);
	soldierCounterB = soldiersB.size();
}
void State::addSoldiers(std::vector<Soldier*>& soldiersVector, Player player) {
	soldiersVector.push_back(new Soldier(player, SoldierType::S1, this));
	soldiersVector.push_back(new Soldier(player, SoldierType::S2, this));
	soldiersVector.push_back(new Soldier(player, SoldierType::S3, this));
}
void State::initBoard() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			board[i][j] = Cell();

	board[flgAPos[0]][flgAPos[1]].setType(CellType::FLAG_A);
	board[flgBPos[0]][flgBPos[1]].setType(CellType::FLAG_B);
	fillCells(forest_positions, forest_size, CellType::FOREST); 
	fillCells(sea_positions, sea_size, CellType::SEA);
}

void State::fillCells(const int *positions, int numCells, CellType type) {
	for (int i = 0; i < numCells; i++) {
		int x = positions[2 * i];
		int y = positions[2 * i + 1];
		board[x][y].setType(type);
	}
}