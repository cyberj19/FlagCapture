#include "Match.h"

Player Match::Play()
{
	int input;
	while (true) {
		graphics.render(state);
		state.step();
		Sleep(80);
		input = controller.getInput();
		state.control(input);
		if (state.isFinished) break;
	}
	return state.winner;
}
