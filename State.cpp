#pragma once
#include "State.h"
#include "Soldier.h"
using namespace std;

State::State(GameSettings settings, BoardConfiguration boardConfig)
	: _settings(settings), 
	  _boardConfig(boardConfig),
	  _changeBuffer(),
	  clock(0), 
	  isFinished(false) {
	initRecorder();
	initGameObjects();
}

void State::initBoard()
{
	for (int y = 0; y < Board::Rows; ++y)
		for (int x = 0; x < Board::Cols; ++x)
			board[y][x] = Cell();

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
	for (int y = 0; y < Board::Rows; ++y)
		for (int x = 0; x < Board::Cols; ++x)
			board[y][x].unsetSoldier();

	initTeams();
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
	initTeams();
}

void State::initTeams() {
	if (_settings.getBoardInitOptions() == BoardOptions::Randomized) {
		getCell(_boardConfig.getFlagAPosition()).setType(CellType::EMPTY);
		getCell(_boardConfig.getFlagBPosition()).setType(CellType::EMPTY);
		_boardConfig.randomizeTeamsPositions();
	}
	
	createSoldiers(soldiersA, Player::A, _boardConfig.getSoldiersAPositions());
	soldierCounterA = (int) soldiersA.size();
	getCell(_boardConfig.getFlagAPosition()).setType(CellType::FLAG_A);
	
	createSoldiers(soldiersB, Player::B, _boardConfig.getSoldiersBPositions());
	soldierCounterB = (int) soldiersB.size();
	getCell(_boardConfig.getFlagBPosition()).setType(CellType::FLAG_B);
}

void State::createSoldiers(vector<Soldier>& soldiers, Player player, vector<Position> positions) {
	soldiers = vector<Soldier>(3);
	for (int s = 0; s < 3; ++s) {
		soldiers[s] = Soldier(this, player, SoldierType(s), positions[s]);
		getCell(positions[s]).setSoldier(&soldiers[s]);
	}
}

bool State::anyMoving()
{
	for (const Soldier& soldier : soldiersA)
		if (soldier.isMoving())
			return true;

	for (const Soldier& soldier : soldiersB)
		if (soldier.isMoving())
			return true;

	return false;
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

	// if a soldier's move is not recorded on its
	// "correct" clock cycle, fix it by rounding
	// to the correct parity
	bool fixClock = soldierId > 3 && clock % 2 == 1 ||
					soldierId <= 3 && clock % 2 == 0;

	newStep += to_string(clock - (fixClock ? 1 : 0));
	newStep += "," + to_string(soldierId) + ",";

	switch (action) {
	case Action::UP: newStep += 'U'; break;
	case Action::DOWN: newStep += 'D'; break;
	case Action::RIGHT: newStep += 'R'; break;
	case Action::LEFT: default: newStep += 'L'; break;
	}

	if (soldierId <= 3)
		stepsBufferA += newStep + "\n";
	else
		stepsBufferB += newStep + "\n";
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

std::string State::getBoardString()
{
	return _boardConfig.getBoardString();
}
