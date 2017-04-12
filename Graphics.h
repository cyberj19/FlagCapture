#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "State.h"
#include "Position.h"
#include "User.h"

enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, OLIVE, WHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW };

class State;

class Graphics {
	State* state;
public:
	Graphics(State* state) : state(state) {}
	void render();
	void renderChange(Position positionToChange);
	void drawBoard();
	void drawEnv();

};		

void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor();
void announceWinner(string winner);