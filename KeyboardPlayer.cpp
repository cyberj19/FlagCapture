#include "KeyboardPlayer.h"
using namespace std;

queue<char> KeyboardPlayer::discarded = queue<char>();

void KeyboardPlayer::processKey(char key, bool storeDiscarded) {
	int idx = _layout.find(key);

	if (idx == string::npos) {
		if (storeDiscarded)
			discarded.push(key);
	}
	else if (idx < 3) // first 3 chars of layout are soldier selection
	{
		if (_layout[idx] != _selectedSoldier)
			_selectedMove = -1;
		_selectedSoldier = _layout[idx];
	}
	else // last 4 chars of layout are dir selection
		_selectedMove = idx - 3;
}
GameMove KeyboardPlayer::play(const GameMove & opponentsMove)
{
	while (!discarded.empty()) {
		processKey(discarded.front(), false);
		discarded.pop();
	}
	while (_kbhit()) {
		processKey(_getch(), true);
	}

	if (_selectedSoldier == -1)
		return GameMove(0, 0, 0, 0);

	int from_x = 0, from_y = 0, to_x = 0, to_y = 0;
	for (int y = 1; y <= _board->rows; y++) {
		for (int x = 1; x <= _board->cols; x++) {
			char bchar = _board->charAt(x, y);
			if (_selectedSoldier == bchar) {
				to_x = from_x = x;
				to_y = from_y = y;
				break;
			}
		}
	}

	if (_selectedMove == -1)
		return GameMove(0, 0, 0, 0);
	if (from_x == 0 || from_y == 0 || to_x == 0 || to_y == 0)
		return GameMove(0, 0, 0, 0);
	switch (_selectedMove) {
	case 0:
		to_y--; break;
	case 1:
		to_y++; break;
	case 2:
		to_x--; break;
	case 3:
	default:
		to_x++; break;
	}

	return GameMove(from_x, from_y, to_x, to_y);
}
