#pragma once
#include "AbstractPlayer.h"
#include "enums.h"

class AlgorithmPlayer : public AbstractPlayer {
	Player _player;
	string _name;
	const BoardData* _board;
public:
	virtual void setPlayer(int player) { _player = (Player)player; }
	virtual string getName()const { return _name; }
	virtual void init(const BoardData& board) { _board = &board; }
	virtual GameMove play(const GameMove& opponentsMove);


};