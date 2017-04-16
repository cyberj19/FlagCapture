#include "Controller.h"

Input Controller::getInput()
{
	Input input = { Action::NOACTION, Player::NONE };
	while (_kbhit()) {
		char ch = _getch();
		input = parse(ch);
		if (input.action != Action::NOACTION)
			state->control(input);
	}
	return input;
}

Controller::Controller(State * state, const char * layoutA, const char * layoutB)
	: state(state), _layoutA(layoutA), _layoutB(layoutB)
{
}

Input matchLayout(Player player, const char* layout, const char ch) {
	int layoutLen = strlen(layout); 
	for (int i = 0; i < layoutLen; i++)
	{
		if (ch == layout[i])
			return { (Action)i, player };

	}
	return { Action::NOACTION, player };
	
	
}

Input Controller::parse(char ch)
{
	if ((int) ch == (int) Action::ESC) return{ Action::ESC, Player::NONE };
	Input input = matchLayout(Player::A, _layoutA, ch);
	if (input.action != Action::NOACTION) return input;
	return matchLayout(Player::B, _layoutB, ch);
}

void Controller::clearBuffer() {
	int in = _kbhit();
	while (in) {
		_getch();
		in = _kbhit();
	}
}