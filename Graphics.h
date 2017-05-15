#pragma once
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
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

void setColorByEntity(std::string entity);
void announceWinner(string winner);
void announceGameStopped();
void printScores(User userA, User userB);
void showErrors(vector<string> errors, bool isQuiet);
void showFinalResults(User userA, User userB, bool isQuiet);
void showMatchResults(int round, int numMoves, MatchOutput result);