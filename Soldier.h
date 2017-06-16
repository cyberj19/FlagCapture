#pragma once
#include "Match.h"
#include "State.h"
#include "enums.h"
#include "Position_203398664.h"


class State;

bool isMatchLines(int myLine, int startLine, int stopLine);

class Soldier {
	State* state;

	Position_203398664 _currentPosition;

	int _dir_x, _dir_y;
	std::string _symbol;
	bool _moving;
	Player _player;
	SoldierType _type;
	SoldierStatus status;

public:
	Soldier();
	Soldier(State *state, Player player, SoldierType type, Position_203398664 pos);
	void step(GameMove move);
	Position_203398664 nextPosition();

	void setCurrentPosition(int x, int y) { _currentPosition.setX(x);  _currentPosition.setY(y); }
	Position_203398664 getCurrentPosition() { return _currentPosition; }
	bool isAlive() { return status == SoldierStatus::ALIVE; }
	std::string getSymbol() { return std::string("[") + std::to_string(getId()) + std::string("] "); }
	Player getPlayer() { return _player; }

	bool isMoving() const { return _moving && (_dir_x != 0 || _dir_y != 0); }
	int getId() const;
private:
	Soldier& battleWinner(Soldier & Attacker, Soldier & Defender, Position_203398664 & battleCell);
	
	bool attack(Soldier& Defender);
	void die();
	void move(Position_203398664 targ);
	void stop() { _dir_x = 0; _dir_y = 0; }
	void win(Position_203398664 targ);

	bool canMoveInSea();
	bool canMoveInForest();
	bool isMyTurn();
};