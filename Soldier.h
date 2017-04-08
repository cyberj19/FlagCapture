#pragma once
#include "Match.h"

enum class SoldierType {S1, S2, S3};

class Soldier {
	int _x, _y;
	int _dir_x, _dir_y;
	char _symbol;
	Player _player;
	SoldierType _type;
public:
	Soldier(Player player, SoldierType type) :_player(player), _type(type) {}
	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	char getSymbol();
	int getNextX();
	int getNextY();

private:
};