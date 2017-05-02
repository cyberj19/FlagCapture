#pragma once
#include "Match.h"
#include "State.h"
#include "enums.h"
#include "Position.h"


class State;

bool isMatchLines(int myLine, int startLine, int stopLine);

class Soldier {
	Position _currentPosition;
	int _dir_x, _dir_y;
	const char* _symbol;
	bool isMoving;
	Player _player;
	SoldierType _type;
	State* state;
	SoldierStatus status;

public:
	Soldier(Player player, SoldierType type, State *state) 
		: state(state), _player(player), _type(type), isMoving(false), status(SoldierStatus::ALIVE) 
	{ 
		state->initBoardPosition(this); 
		setSymbol(); 
	}

	void setCurrentPosition(int x, int y) { _currentPosition.x=x;  _currentPosition.y = y; }
	Position getCurrentPosition() { return _currentPosition; }
	void setState(State* state) { this->state = state; }
	bool isAlive() { return (status == SoldierStatus::ALIVE); }
	Position nextPosition();
	const char* getSymbol();
	void control(Input input);
	void setSymbol();
	void step();
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
	int getId();
};