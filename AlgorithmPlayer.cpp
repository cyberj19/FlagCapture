#include "AlgorithmPlayer.h"

AlgorithmCell& AlgorithmPlayer::sat(int x, int y) const {
	return _soldiers[x - 1 + (y - 1)*_rows];
}
AlgorithmCell& AlgorithmPlayer::bat(int x, int y) const {
	return _background[x - 1 + (y - 1)*_rows];
}
void AlgorithmPlayer::parseBoardChar(int x, int y, char ch) {
	if (ch == 'S') bat(x, y) = AlgorithmCell::sea;
	else if (ch == 'T') bat(x, y) = AlgorithmCell::tree;
	else if (ch == ' ') bat(x, y) = AlgorithmCell::land;
	else if (ch == 'A')
		bat(x, y) = _player == Player::A ?
		AlgorithmCell::meFlag : AlgorithmCell::opFlag;
	else if (ch == 'B')
		bat(x, y) = _player == Player::B ?
		AlgorithmCell::meFlag : AlgorithmCell::opFlag;
	else if (ch == '#')
		sat(x, y) = AlgorithmCell::opx;
	else {
		int id = (ch - '0') % 6;
		if (id == 1) sat(x, y) = AlgorithmCell::me1;
		else if (id == 2) sat(x, y) = AlgorithmCell::me2;
		else sat(x, y) = AlgorithmCell::me3;
	}
}
void AlgorithmPlayer::cacheBoard() {
	for (int x = 1; x <= _boardProxy->cols; x++)
		for (int y = 1; y <= _boardProxy->rows; y++) 
			parseBoardChar(x, y, _boardProxy->charAt(x, y));
}

bool AlgorithmPlayer::validatePosition(int x, int y) {
	return x >= 1 && x <= _boardProxy->cols && y >= 1 && y <= _boardProxy->rows;
}
void AlgorithmPlayer::updateBoard(const GameMove & gameMove)
{
	if (validatePosition(gameMove.from_x, gameMove.from_y))
		parseBoardChar(gameMove.from_x, gameMove.from_y,
			_boardProxy->charAt(gameMove.from_x, gameMove.from_y));

	if (validatePosition(gameMove.to_x, gameMove.to_y))
		parseBoardChar(gameMove.to_x, gameMove.to_y,
			_boardProxy->charAt(gameMove.to_x, gameMove.to_y));
}
void AlgorithmPlayer::setPlayer(int player)
{
	_player = player == 1 ? Player::A : Player::B;
}
void AlgorithmPlayer::init(const BoardData & board)
{
	if (_background != nullptr) delete _background;
	_background = new AlgorithmCell[board.rows*board.cols];

	if (_soldiers != nullptr) delete _soldiers;
	_soldiers = new AlgorithmCell[board.rows*board.cols];
	
	_boardProxy = &board;

	cacheBoard();
}

GameMove AlgorithmPlayer::play(const GameMove & opponentsMove)
{
	updateBoard(opponentsMove);
	GameMove gameMove = GameMove(0, 0, 0, 0);

	updateBoard(gameMove);
	return gameMove;
}
