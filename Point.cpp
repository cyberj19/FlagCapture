#include <Windows.h>
#include "Point.h"


void Point::move()
{
	int new_x = _x + _dir_x;
	if (new_x < MIN_X || new_x > MAX_X) {
		_dir_x = -_dir_x;
	}
	int new_y = _y + _dir_y;
	if (new_y < MIN_Y || new_y > MAX_Y) {
		_dir_y = -_dir_y;
	}

	_x += _dir_x;
	_y += _dir_y;
}


int main() {
	Point points[8];
	int x = 10, y = 10;
	char c = '@';
	for (auto& p : points) {
		p.set(++x, --y);
		p.setChar(c++);
	}
	while (1) {
		for (auto& p : points) {
			p.draw();
		}
		Sleep(50);
		for (auto& p : points) {
			p.erase();
			p.move();
		}
	}
}