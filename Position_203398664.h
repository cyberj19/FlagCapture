#pragma once


class Position_203398664 {
	int x;
	int y;
public:
	Position_203398664(int x=-1, int y=-1): x(x), y(y) {}
	Position_203398664(const Position_203398664 &pos) : x(pos.x), y(pos.y) {}

	bool operator == (Position_203398664 p) {
		return x == p.x && y == p.y;
	}

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x=_x; }
	void setY(int _y) { y = _y; }

	int& operator [](int i) {
		if (i % 2 == 0) return x;
		else return y;
	}
};