#include "AlgorithmPlayer_203398664.h"

AlgorithmRegistration reg("203398664", []() {return new AlgorithmPlayer_203398664(); });

AlgorithmCell_203398664& AlgorithmPlayer_203398664::bat(int x, int y) const {
	return _background[x - 1 + (y - 1)*_boardProxy->rows];
}
void AlgorithmPlayer_203398664::parseBoardChar(int x, int y) {
	char ch = _boardProxy->charAt(x, y);
	if (ch == 'S') bat(x, y) = AlgorithmCell_203398664::sea;
	else if (ch == 'T') bat(x, y) = AlgorithmCell_203398664::tree;
	else if (ch == ' ') bat(x, y) = AlgorithmCell_203398664::land;
	else if (ch == 'A' || ch == 'B') {
		Player flagPlayer = ch == 'A' ? Player::A : Player::B;
		if (_player == flagPlayer) {
			bat(x, y) = AlgorithmCell_203398664::myFlag;
			myFlag = Position_203398664(x, y);
		}
		else {
			bat(x, y) = AlgorithmCell_203398664::opFlag;
			opFlag = Position_203398664(x, y);
		}
	}
	else if (ch == '#') {
		op[indexOfLastChangedEnemy++] = Position_203398664(x, y);
	}
	else {
		int id = (ch - '0') % 6;
		me[id - 1] = Position_203398664(x, y);
	}
}
void AlgorithmPlayer_203398664::cacheBoard() {
	indexOfLastChangedEnemy = 0;
	for (int x = 1; x <= _boardProxy->cols; x++)
		for (int y = 1; y <= _boardProxy->rows; y++) 
			parseBoardChar(x, y);
}

bool AlgorithmPlayer_203398664::validatePosition(int x, int y) {
	return x >= 1 && x <= _boardProxy->cols && y >= 1 && y <= _boardProxy->rows;
}

void AlgorithmPlayer_203398664::updateBoard(const GameMove & gameMove, bool enemyMove)
{
	if (!validatePosition(gameMove.from_x, gameMove.from_y) ||
		!validatePosition(gameMove.to_x, gameMove.to_y))
		return;

	if (enemyMove)
		for (int i = 0; i < 3; i++) {
			if (op[i] == Position_203398664(gameMove.from_x, gameMove.from_y)) {
				indexOfLastChangedEnemy = i;
				break;
			}
		}
	
	parseBoardChar(gameMove.from_x, gameMove.from_y);
	parseBoardChar(gameMove.to_x, gameMove.to_y);
}
void AlgorithmPlayer_203398664::setPlayer(int player)
{
	_player = player == 1 ? Player::A : Player::B;
}

void AlgorithmPlayer_203398664::init(const BoardData & board)
{
	if (_background != nullptr) delete _background;
	_background = new AlgorithmCell_203398664[board.rows*board.cols];
	homingDir = HDir::X;

	_boardProxy = &board;
	historyTracker = MovesHistoryTracker_203398664();
	cacheBoard();
}

GameMove AlgorithmPlayer_203398664::play(const GameMove & opponentsMove)
{
	updateBoard(opponentsMove, true);
	updateBoard(lastGameMove, false);
	lastGameMove = genericPlay(opponentsMove);
	historyTracker.save(lastGameMove);
	return lastGameMove;
}


int towards(int from, int to) {
	return from + (to > from ? 1 : -1);
}

int unwards(int from, int to) {
	return from + (to > from ? -1 : 1);
}

Position_203398664 towards(Position_203398664 from, Position_203398664 to, HDir dir) {
	int n_x = dir == HDir::X ? towards(from[0], to[0]) : from[0];
	int n_y = dir == HDir::Y ? towards(from[1], to[1]) : from[1];
	return Position_203398664(n_x, n_y);
}

Position_203398664 unwards(Position_203398664 from, Position_203398664 to, HDir dir) {
	int n_x = dir == HDir::X ? unwards(from[0], to[0]) : from[0];
	int n_y = dir == HDir::Y ? unwards(from[1], to[1]) : from[1];
	return Position_203398664(n_x, n_y);
}

bool AlgorithmPlayer_203398664::checkCollision(const Position_203398664& curr, HDir dir) {
	Position_203398664 nextPos = towards(curr, opFlag, dir);
	if (nextPos == myFlag)
		return true;

	for (int i = 0; i < 3; i++) {
		if (nextPos == me[i])
			return true;
		if (nextPos == op[i])
			return true;
	}

	return false;
}

GameMove AlgorithmPlayer_203398664::genericPlay(const GameMove& opponentsMove) {
	Position_203398664 sol = _player == Player::A ? me[1] : me[0];
	Position_203398664 nextPos = towards(sol, opFlag, homingDir);
	HDir otherDir = (HDir)(1 - homingDir);
	if (sol[homingDir] == opFlag[homingDir]) {
		homingDir = otherDir;
		return genericPlay(opponentsMove);
	}
	bool collisionInDir = checkCollision(sol, homingDir);
	bool collisionInOtherDir = checkCollision(sol, otherDir);
	
	
	if (collisionInDir) {
		if (collisionInOtherDir) {
			nextPos = unwards(sol, opFlag, homingDir);
			homingDir = otherDir;
		}
		
		else if (sol[otherDir] != opFlag[otherDir]) {
			nextPos = towards(sol, opFlag, otherDir);
		}
		else {
			nextPos = sol;
			int max = homingDir == HDir::X ? _boardProxy->cols : _boardProxy->rows;
			nextPos[otherDir] += sol[otherDir] < max ? 1 : -1;
		}
	}
	GameMove ret = GameMove(sol[0], sol[1], nextPos[0], nextPos[1]);
	if (historyTracker.count(ret) == 3) {

	}
	return ret;
}