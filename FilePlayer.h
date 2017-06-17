#pragma once
#include "State.h"
#include <conio.h>
#include "enums.h"
#include "Input.h"
#include "GameSettings.h"
#include<string>
#include<queue>
#include "Utils.h"
class State;

class FilePlayer : public AbstractPlayer {
	std::queue<std::string> _movesQueue;
	int _player;
	const GameSettings& settings;
	const BoardData* _board;
	GameMove nextMove;
	int nextClock;
public:
	FilePlayer(const GameSettings& settings) : settings(settings), _movesQueue(), nextMove(0,0,0,0) {}
	bool eof() { return _movesQueue.empty();}

	virtual void setPlayer(int player);
	virtual void init(const BoardData& board) { _board = &board; }
	virtual GameMove play(const GameMove& opponentsMove);
	virtual string getName() const { return _player == 1 ? "A" : "B"; }
private:
	void acquireNextMove();
};
