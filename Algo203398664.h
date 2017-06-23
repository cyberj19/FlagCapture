#pragma once
#include "AlgorithmRegistration.h"
#include "AbstractPlayer.h"
#include "Pos203398664.h"
//#include "enums.h"

enum class Player203398664 { A = 1, B = 2, NONE };

class Algo203398664 : public AbstractPlayer {
	// metadata
	Player203398664 _player;

	//technical stuff
	const BoardData* _boardProxy;
	GameMove lastGameMove = GameMove(0, 0, 0, 0);

	//algorithm state
	int _soldier;
	bool isSoldierAlive[3] = { true, true, true };
	Pos203398664 mySoldiers[3];
	Pos203398664 enemyFlag;
public:
	virtual void setPlayer(int player);
	virtual string getName() const { return string("Algorithm 203398664"); }
	virtual void init(const BoardData& board);
	virtual GameMove play(const GameMove& opponentsMove);
private:
	bool isOutOfBounds(int x, int y) const;
	bool isEnemyFlag(int x, int y) const;
	bool isMyFlag(int x, int y) const; 
	bool isEnemy(int x, int y) const; 
	bool isFriend(int x, int y) const;
	bool canMove(int x, int y) const;

	void captureBoard();

	void updateSoldierStatus(const GameMove & opponentsMove);
	void switchSoldier();
	int moveScore(const Pos203398664& nextPos,
					const Pos203398664& lastPos);
	GameMove genericPlay(const GameMove & opponentsMove);
};