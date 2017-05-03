#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "State.h"
#include "Position.h"
#include "User.h"
#include "Utils.h"

enum { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_PURPLE, OLIVE, WHITE, GREY, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW };

class State;

class Graphics {
	State* state;
	bool _recording;
public:
	Graphics(State* state, bool recording) 
		: state(state), _recording(recording) {}
	void render();
	void renderChange(Position positionToChange);
	void drawBoard();
	void drawEnv();
	void renderRecording();
};		


void announceWinner(string winner);
void announceGameStopped();
void printScores(string userA, int scoreA, string userB, int scoreB);
void printSubMenu();