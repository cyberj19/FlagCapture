#pragma once


class Position {
public:
	int x;
	int y;

	Position(int x=-1, int y=-1): x(x), y(y) {}

	bool operator == (Position p) {
		return x == p.x && y == p.y;
	}
};