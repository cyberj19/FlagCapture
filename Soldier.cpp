#include "Soldier.h"

Position Soldier::nextPosition()
{
	Position nextPos = _currentPosition;
	nextPos.x += _dir_y;
	nextPos.y += _dir_x;
	return nextPos;
}

const char * Soldier::getSymbol()
{
	return _symbol;
}

void Soldier::setSymbol()
{
	if (_player == Player::A) {
		switch (_type) {
		case SoldierType::S1:
			_symbol = " 1  ";
			break;
		case SoldierType::S2:
			_symbol = " 2  ";
			break;
		case SoldierType::S3:
		default:
			_symbol = " 3  ";
			break;
		}
	}
	else { // (_player == Player::B)
		switch (_type) {
		case SoldierType::S1:
			_symbol = " 7  ";
			break;
		case SoldierType::S2:
			_symbol = " 8  ";
			break;
		case SoldierType::S3:
		default:
			_symbol = " 9  ";
			break;
		}
	}
}

void Soldier::control(Input input) {
	if (input.player != _player) return;

	_dir_x = 0;
	_dir_y = 0;

	if (input.action == Action::CHOOSE1)
		isMoving = _type == SoldierType::S1;
	else if (input.action == Action::CHOOSE2)
		isMoving = _type == SoldierType::S2;
	else if (input.action == Action::CHOOSE3)
		isMoving = _type == SoldierType::S3;
	else if (isMoving) {
		switch (input.action) {
		case Action::UP: _dir_y = -1; break;
		case Action::DOWN: _dir_y = 1; break;
		case Action::LEFT: _dir_x = -1; break;
		case Action::RIGHT: _dir_x = 1; break;
		}
	}
}
void Soldier::step()
{
	if (!isMoving || !isAlive()) return;
	if (state->getClock() % 2 == 1 && _player == Player::A) {
		stepLogic(Player::A);
	}
	else if (state->getClock() % 2 == 0 && _player == Player::B) {
		stepLogic(Player::B);
	}
}

void Soldier::stepLogic(Player player)
{
	// check direction on board
	Position nextPos = this->nextPosition();
	if (nextPos.x >= COLS || nextPos.x < 0 || nextPos.y >= ROWS || nextPos.y < 0) {
		stop(); 
	}
	//if forest or sea check type - if approved move else do nothing
	else if (state->getCell(nextPos).getType() == CellType::FOREST) {
		if (player == Player::A) {
			if (_type == SoldierType::S2) move();
			else stop();
		}
		else {
			if (_type == SoldierType::S1 || _type == SoldierType::S2) move();
			else stop();
		}
	} //check soldiertype}
	else if (state->getCell(nextPos).getType() == CellType::SEA) {
		if (player == Player::A) {
			if (_type == SoldierType::S2 || _type == SoldierType::S3) move();
			else stop(); 
		}
		else {
			if (_type == SoldierType::S1) move();
			else stop();
		}
	}//check soldiertype}
	

	//if FlagA do nothing, if FlagB move -end game - you winner
	else if (state->getCell(nextPos).getType() == CellType::FLAG_A ) {
		if (player == Player::B) {
			move();
			state->isFinished = true;
			state->winner = Player::B;
		}
		else {stop();}
	}
	else if (state->getCell(nextPos).getType() == CellType::FLAG_B) {
		if (player == Player::A) {
			move();
			state->isFinished = true;
			state->winner = Player::A;
		}
		else {
			stop();
		}
	}

	else {
		//if empty - check if there is an other soldier on this cell (is nullptr?)
		//if there isnt - move
		Soldier* cellSoldier = state->getCell(nextPos).getSoldier();
		if (cellSoldier == nullptr) {
			move();
		}
		// if there is :if playerA -do nothing, if playerB -attack
		else if (cellSoldier->getPlayer() == player) {
			stop();
		}
		else{
			attack(*this, *cellSoldier);
		}
	}
}

// returns the winner of the battle
Soldier & Soldier::battleWinner(Soldier & Attacker, Soldier & Defender, Position & battleCell)
{
	if (Attacker._player == Player::A)
	{
		if (Attacker._type == SoldierType::S1)
			return (isMatchLines(battleCell.x, 9, 12) || isMatchLines(battleCell.y, 3, 3)) ? Defender : Attacker;
		if (Attacker._type == SoldierType::S2) {
			if (Defender._type == SoldierType::S3)
				return Defender;
			else {
				return (isMatchLines(battleCell.x, 2, 3) || isMatchLines(battleCell.y, 10, 10)) ? Attacker : Defender;
			}
		}
		else{ // if (Attacker._type == SoldierType::S3) 
			return (isMatchLines(battleCell.x, 7, 7) || isMatchLines(battleCell.y, 6, 6)) ? Attacker : Defender;
		}	
	}
	else{
		return battleWinner(Defender, Attacker, battleCell); 
	}
}

void Soldier::attack(Soldier & Attacker, Soldier & Defender)
{
	Position battleCell;
	battleCell = Defender.getCurrentPosition();
	Soldier& winner = battleWinner(Attacker, Defender, battleCell);
	if (winner._player == Attacker._player) {
		Defender.die();
		Attacker.move();
	}
	else {
		Attacker.die();
	}
}

void Soldier::die()
{
	state->updateBoardSoldierDied(_currentPosition);
	status = DEAD; 
}

void Soldier::move()
{
	Position nextPos = nextPosition();
	state->updateBoardSoldierMoved(_currentPosition, nextPos);
	_currentPosition = nextPos;

	
}

bool isMatchLines(int myLine, int startLine, int stopLine) {
	for (int i = startLine; i <= stopLine; i++)
	{
		if (myLine == i)
			return true;
	}
	return false;
}

