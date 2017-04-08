#include "Match.h"

Player Match::Play()
{
	int input;
	do{
		graphics.render(state);
		state.step();
		Sleep(80);
		input = controller.getInput();
		state.control(input);
	} while (!state.isFinished);
	return state.winner;
}
