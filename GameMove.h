#pragma once
struct GameMove {
	int from_x, from_y;
	int to_x, to_y;
	//GameMove() : GameMove(0,0,0,0) {}
	GameMove(int x1, int y1, int x2, int y2) : from_x(x1), from_y(y1), to_x(x2), to_y(y2) { }
	/*GameMove(const GameMove& gameMove):
		from_x(gameMove.from_x), from_y(gameMove.from_y),
		to_x(gameMove.to_x), to_y(gameMove.to_y){}

	const GameMove& operator=(const GameMove& gameMove) {
		from_x = gameMove.from_x;
		from_y = gameMove.from_y;
		to_x = gameMove.to_x;
		to_y = gameMove.to_y;

		return *this;
	}*/
};