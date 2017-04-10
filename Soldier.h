#pragma once
#include "Match.h"
#include "State.h"

enum class SoldierType {S1, S2, S3};
enum SoldierStatus{ALIVE, DEAD};

class Soldier {
	int _x, _y;
	int _dir_x, _dir_y;
	char _symbol;
	bool isMoving;
	Player _player;
	SoldierType _type;
	State* state;
	SoldierStatus status;
public:
	Soldier(Player player, SoldierType type) :_player(player), _type(type), isMoving(false), status(ALIVE) {}
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	char getSymbol();
	int getNextX();
	int getNextY();
	void step();
	void control(Input input);
	void setState(State* state) { this->state = state; }
	bool isAlive() { return (status == SoldierStatus::ALIVE); }
private:
	void stepLogic(Soldier& soldier, int command);
	Soldier& battleWinner(Soldier& Attacker, Soldier& Defender);
	void attack(Soldier& Attacker, Soldier& Defender);
	void die() {
		this->status = DEAD;
	}

	void move(int srcX, int srcY, int dstX, int dstY);

};
