#include "Controller.h"

void Controller::getInput()
{
	while (_kbhit()) {
		char ch = _getch();
		Input input = parse(ch);
		if (input.action != Action::NOACTION)
			state->control(input);
	}
		
}

Controller::Controller(State * state, const char * layoutA, const char * layoutB)
	: state(state), _layoutA(layoutA), _layoutB(layoutB)
{
}

Input matchLayout(Player player, const char* layout, const char ch) {
	int layoutLen = strlen(layout); 
	for (int i = 0; i < layoutLen; i++)
	{
		if (ch == layout[i]) {
			Input input = { (Action)i, player };
			return input;
		}
	}
	Input input = { Action::NOACTION, player };
	return input;
	
}

Input Controller::parse(char ch)
{
	
		Input input = matchLayout(Player::A, _layoutA, ch);
		if (input.action != Action::NOACTION) return input;
		return matchLayout(Player::B, _layoutB, ch);

}
