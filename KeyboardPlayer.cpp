#include "KeyboardPlayer.h"


GameMove KeyboardPlayer::play(const GameMove & opponentsMove)
{
	while (_kbhit()) {
		char ch = _getch();
		int idx = _layout.find(ch);
		
		if (idx == string::npos)
			continue;
		else if (idx < 3) // first 3 chars of layout are soldier selection
			_selectedSoldier = _layout[idx];
		else // last 4 chars of layout are dir selection
			_selectedMove = idx - 3;
	}
	
	int from_x, from_y, to_x, to_y;
	for (int y = 1; y < _board->rows; y++) {
		for (int x = 1; x < _board->cols; x++) {
			if (_selectedSoldier == _board->charAt(x, y)) {
				to_x = from_x = x;
				to_y = from_y = y;
			}
		}
	}

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
