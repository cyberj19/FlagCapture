#include "State.h"
#include "Soldier.h"
using namespace std;

State::State(GameSettings settings, BoardConfiguration boardConfig)
	: _settings(settings), _boardConfig(boardConfig),
	  _changeBuffer(), forestPositions(), seaPositions(),
	  clock(0), isFinished(false) {
	initRecorder();
	initGameObjects();
}

void State::initBoard()
{
	for (int y = 0; y < ROWS; ++y)
		for (int x = 0; x < COLS; ++x)
			board[y][x] = Cell();

	getCell(_boardConfig.getFlagAPosition()).setType(CellType::FLAG_A);
	getCell(_boardConfig.getFlagBPosition()).setType(CellType::FLAG_B);
	fillCells(_boardConfig.getSeaPositions(), CellType::SEA);
	fillCells(_boardConfig.getForestPositions(), CellType::FOREST);
}

void State::resetRecorder()
{
	if (_settings.isRecording()) {
		stepsBufferA.clear();
		stepsBufferB.clear();
	}
}

void State::resetGameObjects()
{

	for (int y = 0; y < ROWS; ++y)
		for (int x = 0; x < COLS; ++x)
			board[y][x].unsetSoldier();

	initSoldiers();
}

void State::reset()
{
	clock = 0;
	isFinished = false;

	resetRecorder();
	resetGameObjects();
}

void State::initRecorder()
{
	if (_settings.isRecording()) {
		stepsBufferA = string();
		stepsBufferB = string();
	}
}

void State::initGameObjects()
{
	initBoard();
	initSoldiers();
}

void State::initSoldiers() {
	soldiersA = vector<Soldier>();
	addSoldiers(soldiersA, Player::A, _boardConfig.getSoldiersAPositions());
	soldierCounterA = soldiersA.size();

	soldiersB = vector<Soldier>();
	addSoldiers(soldiersB, Player::B, _boardConfig.getSoldiersBPositions());
	soldierCounterB = soldiersB.size();
}

void State::addSoldiers(vector<Soldier>& soldiersVector, Player player, vector<Position> positions) {
	for (int s = 0; s < 3; ++s) {
		Soldier soldier = Soldier(this, player, SoldierType(s), positions[s]);
		soldiersVector.push_back(soldier);
	}

	for (int s = 0; s < 3; ++s)
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
	if (source == dest) return;

	getCell(dest).setSoldier(getCell(source).getSoldier());
	getCell(source).unsetSoldier();

	_changeBuffer.push_back(dest);
	_changeBuffer.push_back(source);
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
void State::recordAction(int soldierId, Action action)
{
	if (!_settings.isRecording()) return;

	string newStep = string();

	newStep += to_string(clock) + "," + to_string(soldierId) + ",";

	switch (action) {
	case Action::UP: newStep += 'U'; break;
	case Action::DOWN: newStep += 'D'; break;
	case Action::RIGHT: newStep += 'R'; break;
	case Action::LEFT: default: newStep += 'L'; break;
	}

	if (soldierId <= 3)
		stepsBufferA += newStep;
	else
		stepsBufferB += newStep;
}

Position State::popChange() {
	Position back = _changeBuffer.back();
	_changeBuffer.pop_back();
	return back;
}

void State::updateBoardSoldierDied(Position placeOfDeath)
{
	getCell(placeOfDeath).unsetSoldier();
	_changeBuffer.push_back(placeOfDeath);
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
