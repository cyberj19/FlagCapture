#include "Match.h"

Match::Match(const char * keyboardLayoutA, const char * keyboardLayoutB) 
{
	state = new State();
	graphics = new Graphics(state);
	controller = new Controller(state, keyboardLayoutA, keyboardLayoutB);
}

Player Match::Play()
{
	int input;
	graphics->drawBoard();
	graphics->drawEnv();
	do{
		graphics->render();
		state->step();
		Sleep(100);
		controller->getInput();
	} while (!state->isFinished);
	return state->winner;
}
