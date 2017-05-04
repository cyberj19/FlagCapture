#pragma once


class Position {
public:
	int x;
	int y;

	Position(int x=-1, int y=-1): x(x), y(y) {}
	Position(const Position &pos) : x(pos.x), y(pos.y) {}

	bool operator == (Position p) {
		return x == p.x && y == p.y;
	}

	/*const static Position UP = Position(0, 1);
	const static Position DOWN = Position(0, -1);
	const static Position LEFT = Position(-1, 0);
	const static Position RIGHT = Position(1, 0);*/
};