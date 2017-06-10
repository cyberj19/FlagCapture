#pragma once
#include "AbstractPlayer.h"
#include "enums.h"
#include "AlgorithmRegistration.h"
AlgorithmRegistration reg("Jac", []() {return new AlgorithmPlayer(); });
enum class AlgorithmCell {
	none,
	me1, me2, me3, meFlag,
	op1, op2, op3, opx, opFlag,
	land, tree, sea
};
class AlgorithmPlayer : public AbstractPlayer {
	Player _player;
	string _name;
	const BoardData* _boardProxy;
	AlgorithmCell *_background;
	AlgorithmCell *_soldiers;
	int _rows;
public:
	virtual void setPlayer(int player);
	virtual string getName()const { return _name; }
	virtual void init(const BoardData& board);
	virtual GameMove play(const GameMove& opponentsMove);
private:
	AlgorithmCell& bat(int x, int y) const;
	AlgorithmCell& sat(int x, int y) const;
	void parseBoardChar(int x, int y, char ch);
	void cacheBoard();
	void updateBoard(const GameMove& gameMove);
	bool validatePosition(int x, int y);
};