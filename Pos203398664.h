#pragma once


class Pos203398664 {
	int x;
	int y;
public:
	Pos203398664(int x=-1, int y=-1): x(x), y(y) {}
	Pos203398664(const Pos203398664 &pos) : x(pos.x), y(pos.y) {}

	bool operator == (const Pos203398664& p) {
		return x == p.x && y == p.y;
	}

	Pos203398664 Up() { return Pos203398664(x, y - 1); }
	Pos203398664 Down() { return Pos203398664(x, y + 1); }
	Pos203398664 Left() { return Pos203398664(x - 1 , y); }
	Pos203398664 Right() { return Pos203398664(x + 1, y); }

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x=_x; }
	void setY(int _y) { y = _y; }

	int& operator [](int i) {
		if (i % 2 == 0) return x;
		else return y;
	}
};