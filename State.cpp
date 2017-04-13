#include "State.h"
#include "Soldier.h"
#include <time.h>


const int State::forest_positions[22] = { 6,0,   7,0,     6,1,    3,2,    4,2,    5,2,    6,2,     5,3,    6,3,    7,3,     8,3 };
const int State::sea_positions[28] = { 5,7,   4,8,    5,8,    3,9,   4,9,   5,9,   6,9,   7,9,   8,9,   9,9,  6,10,   7,10,   8,10,   7,11 };
const int State::flgAPos[2] = { 0,10 };
const int State::flgBPos[2] = { 12,1 };


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

void State::updateBoardSoldierDied(Position placeOfDeath)
{
	board[placeOfDeath.x][placeOfDeath.y].unsetSoldier();
	boardChanges[0] = placeOfDeath;
	boardChanges[1] = placeOfDeath;
}

void State::initBoardPosition(Soldier* soldier) {
	Player player = soldier->getPlayer();
	if (player == Player::A) {
		int randomIndex = rand() % freePositionsA.size();
		soldier->setCurrentPosition(freePositionsA[randomIndex].x, freePositionsA[randomIndex].y);
		board[freePositionsA[randomIndex].x][freePositionsA[randomIndex].y].setSoldier(soldier);
		freePositionsA.erase(freePositionsA.begin() + randomIndex);
	}
	else { // (player == Player::B)
		int randomIndex = rand() % freePositionsB.size();
		soldier->setCurrentPosition(freePositionsB[randomIndex].x, freePositionsB[randomIndex].y);
		board[freePositionsB[randomIndex].x][freePositionsB[randomIndex].y].setSoldier(soldier);
		freePositionsB.erase(freePositionsB.begin() + randomIndex);
	}
}


void State::soldiersFactory() {
	srand(time(NULL));
	soldiersA = std::vector<Soldier*>();
	addSoldiers(soldiersA, Player::A);
	soldiersB = std::vector<Soldier*>();
	addSoldiers(soldiersB, Player::B);
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

	for (int i = 0; i < 11; i++) {
		int x = forest_positions[2 * i];
		int y = forest_positions[2 * i + 1];
		board[x][y].setType(CellType::FOREST);
	}

	for (int i = 0; i < 14; i++) {
		int x = sea_positions[2 * i];
		int y = sea_positions[2 * i + 1];
		board[x][y].setType(CellType::SEA);
	}
}