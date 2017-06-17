#include "FilePlayer.h"
#include <fstream>
#include <vector>

using namespace std;
GameMove FilePlayer::play(const GameMove& opponentsMove) {
	GameMove ret = nextMove;
	acquireNextMove();
	return ret;
}

void FilePlayer::acquireNextMove() {
	if (_movesQueue.empty()) return;
	string move = _movesQueue.front();
	_movesQueue.pop();

	vector<string> parts = split(move, ",");
	trim(parts);

	nextClock = stoi(parts[0]);
	int soldierId = stoi(parts[1]);
	int from_x = 0, from_y = 0, to_x = 0, to_y = 0;
	for (int y = 1; y <= _board->rows; y++) {
		for (int x = 1; x <= _board->cols; x++) {
			char bchar = _board->charAt(x, y);
			if (soldierId + '0' == bchar) {
				to_x = from_x = x;
				to_y = from_y = y;
				break;
			}
		}
	}

	if (parts[2] == "U") to_y--;
	else if (parts[2] == "D") to_y++;
	else if (parts[2] == "R") to_x++;
	else if (parts[2] == "L") to_x--;

	nextMove = GameMove(from_x, from_y, to_x, to_y);
}

void FilePlayer::setPlayer(int player) {
	_player = player;
	string filePath;
	if (player == 1)
		filePath = settings.getMovesAInputFilePath();
	else
		filePath = settings.getMovesBInputFilePath();

	ifstream infile(filePath);
	string moves((istreambuf_iterator<char>(infile)), istreambuf_iterator<char>());
	infile.close();
	vector<string> vec = split(moves, string("\n\r"));

	_movesQueue = queue<string>();
	for (const string& str : vec)
		_movesQueue.push(str);
	acquireNextMove();
}