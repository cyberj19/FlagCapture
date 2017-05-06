#include "Soldier.h"

Soldier::Soldier(State *state, Player player, SoldierType type, Position pos)
	: state(state), _player(player), _type(type), _moving(false), status(SoldierStatus::ALIVE),
	_currentPosition(pos)
{
	setSymbol();
}

Position Soldier::nextPosition()
{
	Position nextPos = _currentPosition;
	nextPos.setX(nextPos.getX() + _dir_x);
	nextPos.setY(nextPos.getY() + _dir_y);
	return nextPos;
}

void Soldier::setSymbol()
{
	if (_player == Player::A) {
		switch (_type) {
		case SoldierType::S1:
			_symbol = "[1] ";
			break;
		case SoldierType::S2:
			_symbol = "[2] ";
			break;
		case SoldierType::S3:
		default:
			_symbol = "[3] ";
			break;
		}
	}
	else { // (_player == Player::B)
		switch (_type) {
		case SoldierType::S1:
			_symbol = "[7] ";
			break;
		case SoldierType::S2:
			_symbol = "[8] ";
			break;
		case SoldierType::S3:
		default:
			_symbol = "[9] ";
			break;
		}
	}
}

void Soldier::control(Input input) {
	if (input.player != _player) return;

	if (input.action == Action::CHOOSE1)
		_moving = _type == SoldierType::S1;
	else if (input.action == Action::CHOOSE2)
		_moving = _type == SoldierType::S2;
	else if (input.action == Action::CHOOSE3)
		_moving = _type == SoldierType::S3;
	else if (_moving) {
		parseAction(input.action);
	}
}

void Soldier::parseAction(Action action) {
	int _old_dir_x = _dir_x;
	int _old_dir_y = _dir_y;

	_dir_x = _dir_y = 0;
	switch (action) {
	case Action::UP: _dir_y = -1; break;
	case Action::DOWN: _dir_y = 1; break;
	case Action::LEFT: _dir_x = -1; break;
	case Action::RIGHT: _dir_x = 1; break;
	}

	if (_dir_x != _old_dir_x || _dir_y != _old_dir_y)
		state->recordAction(getId(), action);
}

bool Soldier::isMyTurn() {
	if (state->getClock() % 2 == 1 && _player == Player::A)
		return true;
	else if (state->getClock() % 2 == 0 && _player == Player::B) 
		return true;
	else
		return false;
}

int Soldier::getId()
{
	int id;
	switch (_type) {
	case SoldierType::S1:
		id = 1;
		break;
	case SoldierType::S2:
		id = 2;
		break;
	case SoldierType::S3:
	default:
		id = 3;
		break;
	}
	if (_player == Player::B) {
		id += 6;
	}

	return id;
}
void Soldier::step()
{
	if (!isMoving() || !isAlive() || !isMyTurn()) return;
	stepLogic();
}

bool Soldier::canMoveInSea() {
	if (_player == Player::A) return _type == SoldierType::S2;
	else return _type == SoldierType::S1;
}

bool Soldier::canMoveInForest() {
	if (_player == Player::A) return _type == SoldierType::S2 || _type == SoldierType::S3;
	else return _type == SoldierType::S1 || _type == SoldierType::S3;
}
void Soldier::stepLogic()
{
	Position nextPos = this->nextPosition();
	if (nextPos.getX() >= COLS || nextPos.getX() < 0 || nextPos.getY() >= ROWS || nextPos.getY() < 0) {
		stop(); 
		return;
	}
	Cell nextCell = state->getCell(nextPos);
	CellType cellType = nextCell.getType();
	if (cellType == CellType::FLAG_A ) {
		if (_player == Player::B) win(_player);
		else stop();
	}
	else if (cellType == CellType::FLAG_B) {
		if (_player == Player::A) win(_player);
		else stop();
	}
	else if (cellType == CellType::FOREST && !canMoveInForest())
		stop();
	else if (cellType == CellType::SEA && !canMoveInSea())
		stop();
	else {
		Soldier* cellSoldier = nextCell.getSoldier();
		if (cellSoldier == nullptr) move(); 
		else if (cellSoldier->_player == _player) stop();
		else attack(*cellSoldier);
	}
}

void Soldier::win(Player player) {
	move();
	state->winner = player;
	state->isFinished = true;
}

// returns the winner of the battle
Soldier & Soldier::battleWinner(Soldier & Attacker, Soldier & Defender, Position & battleCell)
{
	Soldier & SoldierOfA = Attacker._player == Player::A ? Attacker : Defender;
	Soldier & SoldierOfB = Attacker._player == Player::A ? Defender : Attacker;

	if (SoldierOfA._type == SoldierType::S1)
		return (isMatchLines(battleCell.getY(), 9, 12) || 
				isMatchLines(battleCell.getX(), 3, 3)) ? SoldierOfB : SoldierOfA;
	if (SoldierOfA._type == SoldierType::S2) {
		if (SoldierOfB._type == SoldierType::S3)
			return SoldierOfB;
		else {
			return (isMatchLines(battleCell.getY(), 2, 3) || 
					isMatchLines(battleCell.getX(), 10, 10)) ? SoldierOfA : SoldierOfB;
		}
	}
	else{ // if (SoldierOfA._type == SoldierType::S3) 
		return (isMatchLines(battleCell.getY(), 7, 7) || 
				isMatchLines(battleCell.getX(), 6, 6)) ? SoldierOfA : SoldierOfB;
	}	
}

void Soldier::attack(Soldier & Defender)
{
	Position battleCell;
	battleCell = Defender.getCurrentPosition();
	Soldier& winner = battleWinner(*this, Defender, battleCell);
	if (winner._player == _player) {
		Defender.die();
		move();
	}
	else {
		die();
	}
}

void Soldier::die()
{
	state->notifySoldierDied(this);
	status = SoldierStatus::DEAD; 
}

void Soldier::move()
{
	Position nextPos = nextPosition();
	state->updateBoardSoldierMoved(_currentPosition, nextPos);
	_currentPosition = nextPos;
}

bool isMatchLines(int myLine, int startLine, int stopLine) {
	return startLine <= myLine && myLine <= stopLine;
}

