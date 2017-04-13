#pragma once

#include <iostream>
#include "Utils.h"

using namespace std;

class Point {
	enum { MIN_X = 0, MAX_X = 79, MIN_Y = 0, MAX_Y = 24 };
	int _x = 1, _y = 1;
	char _c = '*';
	int _dir_x = 1, _dir_y = 1;
public:
	void set(int x, int y, int dir_x = 1, int dir_y = 1) {
		_x = x;
		_y = y;
		_dir_x = dir_x;
		_dir_y = dir_y;
	}
	void setChar(char c) {
		_c = c;
	}
	void draw() {
		draw(_c);
	}
	void erase() {
		draw(' ');
	}
	void move();
private:
	void draw(char c) {
		gotoxy(_x, _y);
		cout << c;
		// make sure it gets to screen on time
		cout.flush();
	}
};
