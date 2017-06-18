#include "Algo203398664.h"

AlgorithmRegistration reg("203398664", []() {return new Algo203398664(); });


bool Algo203398664::isOutOfBounds(int x, int y) const
{
	return x < 1 || x>_boardProxy->cols || y < 1 || y>_boardProxy->rows;
}

bool Algo203398664::isEnemyFlag(int x, int y) const
{
	if (_player == Player::A)
		return _boardProxy->charAt(x, y) == 'B';
	else
		return _boardProxy->charAt(x, y) == 'A';
}

bool Algo203398664::isMyFlag(int x, int y) const
{
	if (_player == Player::A)
		return _boardProxy->charAt(x, y) == 'A';
	else
		return _boardProxy->charAt(x, y) == 'B';
}

bool Algo203398664::isEnemy(int x, int y) const
{
	return _boardProxy->charAt(x, y) == '#';
}

bool Algo203398664::isFriend(int x, int y) const
{
	char ch = _boardProxy->charAt(x, y);
	return '0' <= ch && ch <= '9';
}

bool Algo203398664::canMove(int x, int y) const
{
	char ch = _boardProxy->charAt(x, y);
	if (ch == 'S') {
		if (_player == Player::A)
			return _soldier == 1 || _soldier == 2;
		else
			return _soldier == 0 || _soldier == 2;
	}
	else if (ch == 'T') {
		if (_player == Player::A)
			return _soldier == 1;
		else
			return _soldier == 0 || _soldier == 1;
	}
}

void Algo203398664::captureBoard()
{
	for (int x = 1; x <= _boardProxy->cols; x++) {
		for (int y = 1; y <= _boardProxy->rows; y++) {
			if (isEnemyFlag(x, y))
				enemyFlag = Pos203398664(x, y);

			if (isFriend(x, y)) {
				char c = _boardProxy->charAt(x, y);
				int id = (c - '0') % 6 - 1;
				mySoldiers[id] = Pos203398664(x, y);
			}
		}
	}
}

void Algo203398664::setPlayer(int player)
{
	if (player == 1) {
		_player = Player::A;
		_soldier = 1; 
	}
	else {
		_player = Player::B;
		_soldier = 0;
	}
}

void Algo203398664::init(const BoardData & board)
{
	_boardProxy = &board;
	captureBoard();
}

GameMove Algo203398664::play(const GameMove & opponentsMove)
{
	updateSoldierStatus(opponentsMove);
	lastGameMove = genericPlay(opponentsMove);
	return lastGameMove;
}



void Algo203398664::updateSoldierStatus(const GameMove & opponentsMove)
{
	if (lastGameMove.to_x == 0 || lastGameMove.to_y == 0 ||
		lastGameMove.from_x == 0 || lastGameMove.from_y == 0)
		return;

	for (int i = 0; i < 3; i++) {
		if (opponentsMove.to_x == mySoldiers[i].getX() &&
			opponentsMove.to_y == mySoldiers[i].getY()) {

			char c = _boardProxy->charAt(lastGameMove.to_x, lastGameMove.to_y);
			if ((c - '0') % 6 - 1 != i) {
				isSoldierAlive[i] = false;
			}
			break;
		}
	}

	char c = _boardProxy->charAt(lastGameMove.to_x, lastGameMove.to_y);
	if ((c - '0') % 6 - 1 != _soldier){
		isSoldierAlive[_soldier] = false;
		switchSoldier();
	}
	else {
		mySoldiers[_soldier] = Pos203398664(lastGameMove.to_x, lastGameMove.to_y);
	}

}

void Algo203398664::switchSoldier()
{
	do {
		_soldier = (_soldier + 1) % 3;
	} while (!isSoldierAlive[_soldier]);
}

int Algo203398664::moveScore(const Pos203398664& nextPos,
	const Pos203398664& lastPos)
{
	int x = nextPos.getX(), y = nextPos.getY();
	if (isOutOfBounds(x, y)) return 1000;

	if (isEnemyFlag(x, y)) return 0;
	if (isMyFlag(x, y)) return 1000;
	if (isEnemy(x, y) || isFriend(x,y)) return 1000;
	if (!canMove(x, y)) return 1000;

	int dist = abs(enemyFlag.getX() - nextPos.getX()) +
		abs(enemyFlag.getY() - nextPos.getY());

	if (lastPos.getX() == nextPos.getX() &&
		lastPos.getY() == nextPos.getY()) dist++;
	return dist;
}


GameMove Algo203398664::genericPlay(const GameMove& opponentsMove) {
	Pos203398664 sol = mySoldiers[_soldier];
	
	const Pos203398664 lastPos = Pos203398664(lastGameMove.from_x,
		lastGameMove.from_y);

	Pos203398664 dirs[4] = {
		sol.Up(), sol.Down(), sol.Left(), sol.Right()
	};
	int scores[4];

	for (int i = 0; i < 4; i++)
		scores[i] = moveScore(dirs[i], lastPos);

	int bestMoveScore = 1001, bestMoveIndex = 0;
	for (int i = 0; i < 4; i++) {
		if (scores[i] < bestMoveScore) {
			bestMoveScore = scores[i];
			bestMoveIndex = i;
		}
	}

	return GameMove(sol.getX(), sol.getY(),
					dirs[bestMoveIndex].getX(), dirs[bestMoveIndex].getY());
}