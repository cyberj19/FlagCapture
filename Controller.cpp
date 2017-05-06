#include "Controller.h"
#include <fstream>

using namespace std;

Input Controller::getInput() {
	if (_movesOptions == MovesSourceOptions::FromFile)
		return getInputFromFiles();
	else
		return getInputFromKeyboard();
}

Input Controller::getInputFromFiles()
{
	if (state->getClock() == _nextMoveA) {
		string moveString = _movesAList.front();
		_movesAList.erase(_movesAList.begin());
		Input ret = applyMove(moveString);
		_nextMoveA = _movesAList.empty() ? -1 : parseClock(_movesAList.front());
		return ret;
	}

	if (state->getClock() == _nextMoveB) {
		string moveString = _movesBList.front();
		_movesBList.erase(_movesBList.begin());
		Input ret = applyMove(moveString);
		_nextMoveB = _movesBList.empty() ? -1 : parseClock(_movesBList.front());
		return ret;
	}

	return{ Action::NOACTION, Player::NONE };
}

Input Controller::getInputFromKeyboard()
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

Input Controller::applyMove(std::string moveString)
{
	vector<string> parts = split(moveString, ",");
	int soldierId = atoi(parts[1].c_str());

	Player player = soldierId <= 3 ? Player::A : Player::B;
	if (soldierId >= 7) soldierId -= 6;

	Action choose;
	Action dir;

	if (soldierId == 1) choose = Action::CHOOSE1;
	else if (soldierId == 2) choose = Action::CHOOSE2;
	else if (soldierId == 3) choose = Action::CHOOSE3;
	else {
		//error
	}
	if (parts[2] == "U") dir = Action::UP;
	else if (parts[2] == "D") dir = Action::DOWN;
	else if (parts[2] == "R") dir = Action::RIGHT;
	else if (parts[2] == "L") dir = Action::LEFT;
	else {//error 
	}

	state->control({ choose, player });
	state->control({ dir, player });

	return { dir, player };
}

void Controller::getNextMoves()
{
	_nextMoveA = _movesAList.empty() ? -1 : parseClock(_movesAList.front());
	_nextMoveB = _movesBList.empty() ? -1 : parseClock(_movesBList.front());
}

Controller::Controller(State * state, GameSettings settings)
	: state(state), 
	_movesOptions(settings.getMovesOptions()),
	_layoutA(settings.getKeyboardLayoutA()), 
	_layoutB(settings.getKeyboardLayoutB())
{
	if (_movesOptions == MovesSourceOptions::FromFile) {
		loadMovesFiles(settings.getMovesAInputFilePath(),
			settings.getMovesBInputFilePath());
	}
}


Input matchLayout(Player player, const string layout, const char ch) {
	int len = layout.length();
	for (int i = 0; i < len; i++) {
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

void Controller::loadMovesFiles(std::string movesAInputFilePath, std::string movesBInputFilePath)
{
	ifstream infile(movesAInputFilePath);
	string moves((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
	_movesAList = split(moves, string("\n\t\r "));
	infile.close();

	infile = ifstream(movesBInputFilePath);
	moves = string((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
	_movesBList = split(moves, string("\n\t\r "));
	infile.close();

	getNextMoves();
}

void Controller::clearBuffer() {
	int in = _kbhit();
	while (in) {
		_getch();
		in = _kbhit();
	}
}

int parseClock(string moveString)
{
	return atoi(split(moveString, string(",")).front().c_str());
}
