#pragma once

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdbool.h>

#include "enums.h"

using namespace std;

class CommandLineParameters {

	Board board;  //enum: F, R
	Moves moves;  //enum: F, K
	string path;
	bool quiet;
	int delay;

public:
	CommandLineParameters(char *argv[], int argc) : board(Board::R), moves(Moves::K), path(nullptr), quiet(false), delay(20) {}
	Board getBoard() const { return board; }
	Moves getMoves() const { return moves; }
	string getPath() const { return path; }
	bool getQuiet() const;
	int getDelay() const;
};