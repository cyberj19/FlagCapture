#pragma once


class Position {
	int x;
	int y;
public:
	Position(int x=-1, int y=-1): x(x), y(y) {}
	Position(const Position &pos) : x(pos.x), y(pos.y) {}

	bool operator == (Position p) {
		return x == p.x && y == p.y;
	}

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x=_x; }
	void setY(int _y) { y = _y; }
};