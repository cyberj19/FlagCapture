#pragma once
#include "Match.h"
#include "State.h"
#include "enums.h"
#include "Position.h"


class State;

bool isMatchLines(int myLine, int startLine, int stopLine);

class Soldier {
	Position _currentPosition;
	//Position _direction;

	int _dir_x, _dir_y;
	const char* _symbol;
	bool _moving;
	Player _player;
	SoldierType _type;
	State* state;
	SoldierStatus status;

public:
	Soldier(State *state, Player player, SoldierType type, Position pos);
	void control(Input input);
	void step();
	Position nextPosition();

	//Position getDirection() { return _direction; }
	void setCurrentPosition(int x, int y) { _currentPosition.setX(x);  _currentPosition.setY(y); }
	Position getCurrentPosition() { return _currentPosition; }
	bool isAlive() { return status == SoldierStatus::ALIVE; }
	const char* getSymbol() { return _symbol; }
	Player getPlayer() { return _player; }

private:
	void stepLogic();
	Soldier& battleWinner(Soldier & Attacker, Soldier & Defender, Position & battleCell);
	
	void attack(Soldier& Defender);
	void die();
	void move();
	void stop() { _dir_x = 0; _dir_y = 0; }
	void win(Player player);

	bool canMoveInSea();
	bool canMoveInForest();
	bool isMyTurn();
	bool isMoving() { return _moving && (_dir_x != 0 || _dir_y != 0); }

	int getId();
	void setSymbol();
};