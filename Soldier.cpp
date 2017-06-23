#include "Soldier.h"

Soldier::Soldier() :
	state(nullptr), _player(Player203398664::A), _type(SoldierType::S1), _moving(false),
	status(SoldierStatus::ALIVE), _currentPosition(0,0), _symbol("") {}

Soldier::Soldier(State *state, Player203398664 player, SoldierType type, Pos203398664 pos)
	: state(state), _player(player), _type(type), _moving(false), status(SoldierStatus::ALIVE),
	_currentPosition(pos)
{}

Pos203398664 Soldier::nextPosition()
{
	Pos203398664 nextPos = _currentPosition;
	nextPos.setX(nextPos.getX() + _dir_x);
	nextPos.setY(nextPos.getY() + _dir_y);
	return nextPos;
}

bool Soldier::isMyTurn() {
	if (state->getClock() % 2 == 1 && _player == Player203398664::A)
		return true;
	else if (state->getClock() % 2 == 0 && _player == Player203398664::B) 
		return true;
	else
		return false;
}

int Soldier::getId() const
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
	if (_player == Player203398664::B) {
		id += 6;
	}

	return id;
}
void Soldier::step(GameMove gameMove)
{
	if (!isAlive()) return; 
	Pos203398664 nextPos(gameMove.to_x - 1, gameMove.to_y - 1);
	if (nextPos.getX() >= Board::Cols || nextPos.getX() < 0
		|| nextPos.getY() >= Board::Rows || nextPos.getY() < 0) {
		stop();
		return;
	}
	Cell nextCell = state->getCell(nextPos);
	CellType cellType = nextCell.getType();
	if (cellType == CellType::FLAG_A) {
		if (_player == Player203398664::B) win(nextPos);
		else stop();
	}
	else if (cellType == CellType::FLAG_B) {
		if (_player == Player203398664::A) win(nextPos);
		else stop();
	}
	else if (cellType == CellType::FOREST && !canMoveInForest())
		stop();
	else if (cellType == CellType::SEA && !canMoveInSea())
		stop();
	else {
		Soldier* cellSoldier = nextCell.getSoldier();
		if (cellSoldier == nullptr) 
			move(nextPos);
		else if (cellSoldier->_player == _player) 
			stop();
		else if (attack(*cellSoldier)) {
			cellSoldier->die();
			move(nextPos);
		}
		else
			die();
	}
}

bool Soldier::canMoveInSea() {
	if (_player == Player203398664::A) 
		return _type == SoldierType::S2 || _type == SoldierType::S3;
	else 
		return _type == SoldierType::S1 || _type == SoldierType::S3;
}

bool Soldier::canMoveInForest() {
	if (_player == Player203398664::A)
		return _type == SoldierType::S2;
	else 
		return _type == SoldierType::S1 || _type == SoldierType::S2;
}
void Soldier::win(Pos203398664 nextPos) {
	move(nextPos);
	state->winner = _player;
	state->isFinished = true;
}

// returns the winner of the battle
Soldier & Soldier::battleWinner(Soldier & Attacker, Soldier & Defender, Pos203398664 & battleCell)
{
	Soldier & SoldierOfA = Attacker._player == Player203398664::A ? Attacker : Defender;
	Soldier & SoldierOfB = Attacker._player == Player203398664::A ? Defender : Attacker;

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

bool Soldier::attack(Soldier & Defender)
{
	Pos203398664 battleCell;
	battleCell = Defender.getCurrentPosition();
	Soldier& winner = battleWinner(*this, Defender, battleCell);
	return winner._player == _player;
}

void Soldier::die()
{
	stop();
	state->notifySoldierDied(this);
	status = SoldierStatus::DEAD; 
}

void Soldier::move(Pos203398664 targ)
{
	state->updateBoardSoldierMoved(_currentPosition, targ);
	_currentPosition = targ;
}

bool isMatchLines(int myLine, int startLine, int stopLine) {
	return startLine <= myLine && myLine <= stopLine;
}

