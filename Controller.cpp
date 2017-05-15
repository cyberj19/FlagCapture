#include "Controller.h"
#include <fstream>
#include <vector>

using namespace std;
bool validateMove(string moveString, int currClock) {
	vector<string> parts = split(moveString, ",");
	trim(parts);
	if (parts.size() != 3) return false;
	
	int clock = atoi(parts[0].c_str());
	if (clock < currClock) return false;

	int soldier = atoi(parts[1].c_str());
	if (!(soldier >= 1 && soldier <= 3) && !(soldier >= 7 && soldier <= 9))
		return false;
	
	if (parts[2] == "U" || parts[2] == "D" || parts[2] == "L" || parts[2] == "R")
		return true;
	return false;
}
int getNextMove(vector<string>& moves, int clock) {
	while (!moves.empty() && !validateMove(moves.front(), clock))
		moves.erase(moves.begin());
	return moves.empty() ? -1 : parseClock(moves.front());
}
Input Controller::getInput() {
	if (_movesOptions == InputOptions::FromFile)
		return getInputFromFiles();
	else
		return getInputFromKeyboard();
}

Input Controller::applyNextMove(int &nextMove, vector<string>& moves) {
	string moveString = moves.front();
	moves.erase(moves.begin());
	Input ret = applyMove(moveString);
	nextMove = getNextMove(moves, _state->getClock());
	return ret;
}

Input Controller::getInputFromFiles(){
	if (_state->getClock() == _nextMoveA)
		return applyNextMove(_nextMoveA, _movesAList);

	if (_state->getClock() == _nextMoveB)
		return applyNextMove(_nextMoveB, _movesBList);

	return Input(Action::NOACTION, Player::NONE);
}

Input Controller::getInputFromKeyboard(){
	Input input = Input(Action::NOACTION, Player::NONE);
	while (_kbhit()) {
		char ch = _getch();
		input = parseKey(ch);
		if (input.getAction() != Action::NOACTION)
			_state->control(input);
	}
	return input;
}

Input Controller::applyMove(std::string moveString){
	vector<string> parts = split(moveString, ",");
	trim(parts);
	int soldierId = atoi(parts[1].c_str());

	Player player = soldierId <= 3 ? Player::A : Player::B;
	if (soldierId >= 7) soldierId -= 6;

	Action choose;
	Action dir;

	if (soldierId == 1) choose = Action::CHOOSE1;
	else if (soldierId == 2) choose = Action::CHOOSE2;
	else if (soldierId == 3) choose = Action::CHOOSE3;
	if (parts[2] == "U") dir = Action::UP;
	else if (parts[2] == "D") dir = Action::DOWN;
	else if (parts[2] == "R") dir = Action::RIGHT;
	else if (parts[2] == "L") dir = Action::LEFT;

	_state->control({ choose, player });
	_state->control({ dir, player });
	_moveCounter++;
	return{ dir, player };
}


void Controller::getNextMoves(){
	_nextMoveA = getNextMove(_movesAList, _state->getClock());
	_nextMoveB = getNextMove(_movesBList, _state->getClock());
}

Controller::Controller(State * state, const GameSettings& settings)
	: _state(state), 
	_moveCounter(0),
	_movesOptions(settings.getMovesOptions()),
	_layoutA(settings.getKeyboardLayoutA()), _layoutB(settings.getKeyboardLayoutB())
{
	if (_movesOptions == InputOptions::FromFile)
		loadMovesFiles(settings.getMovesAInputFilePath(),
			settings.getMovesBInputFilePath());
}


Input matchLayout(Player player, string layout, char ch) {
	size_t len = layout.length();
	for (size_t i = 0; i < len; i++) {
		if (ch == layout[i])
			return { (Action)i, player };
	}
	return { Action::NOACTION, player };
}

Input Controller::parseKey(char ch){
	if ((int)ch == (int)Action::ESC) return Input(Action::ESC, Player::NONE);
	Input input = matchLayout(Player::A, _layoutA, tolower(ch));
	if (input.getAction() != Action::NOACTION) return input;
	return matchLayout(Player::B, _layoutB, tolower(ch));
}

void loadTeamMoveFile(const string& filePath, vector<string>& movesList) {
	if (filePath == "") {
		movesList = vector<string>();
		return;
	}
	ifstream infile(filePath);
	string moves((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
	movesList = split(moves, string("\n\r"));
	infile.close();
}

void Controller::loadMovesFiles(string movesAInputFilePath, string movesBInputFilePath){
	loadTeamMoveFile(movesAInputFilePath, _movesAList);
	loadTeamMoveFile(movesBInputFilePath, _movesBList);
	getNextMoves();
}

void Controller::clearBuffer() {
	int in = _kbhit();
	while (in) {
		_getch();
		in = _kbhit();
	}
}

int parseClock(string moveString){
	return atoi(split(moveString, string(",")).front().c_str());
}