#pragma once
#include "AlgorithmRegistration.h"
#include "AbstractPlayer.h"
#include "Position_203398664.h"
#include "enums.h"

class MovesHistoryTracker_203398664 {
	int _currentSize;
	int _maxSize;

	std::vector<GameMove> _history;

public:
	MovesHistoryTracker_203398664(int maxSize = 10) : _maxSize(maxSize), _currentSize(0), _history() {}

	void save(GameMove move) {
		if (_currentSize < _maxSize) {
			_history.push_back(move);
			_currentSize++;
		}
		else {
			_history.erase(_history.begin());
			_history.push_back(move);
		}
	}

	int count(GameMove move) {
		int c = 0;
		for (const GameMove& imove : _history) {
			if (move.to_x == imove.to_x && move.to_y == imove.to_y)
				c++;
		}
		return c;
	}
};

enum class AlgorithmCell_203398664 {
	none,land, tree, sea,
	myFlag, opFlag
};

enum HDir { X, Y };
class AlgorithmPlayer_203398664 : public AbstractPlayer {
	// metadata
	Player _player;

	//technical stuff
	const BoardData* _boardProxy;
	GameMove lastGameMove = GameMove(0, 0, 0, 0);

	//state maintenance stuff
	AlgorithmCell_203398664 *_background;
	Position_203398664 me[3], myFlag;
	Position_203398664 op[3], opFlag;
	int indexOfLastChangedEnemy = 0;

	//algorithm state
	HDir homingDir;
	int clock = 0;
	int chaseFlagDir = 0; // 0 - x, 1 - y
	int _soldier;
	MovesHistoryTracker_203398664 historyTracker;

public:
	virtual void setPlayer(int player);
	virtual string getName() const { return string("Algorithm 203398664"); }
	virtual void init(const BoardData& board);
	virtual GameMove play(const GameMove& opponentsMove);

	~AlgorithmPlayer_203398664() {
		if (_background != nullptr)
			delete []_background;
	}
private:
	AlgorithmCell_203398664& bat(int x, int y) const;
	void parseBoardChar(int x, int y);
	void cacheBoard();
	void updateBoard(const GameMove& gameMove, bool enemyMove);
	bool validatePosition(int x, int y);

	bool checkCollision(const Position_203398664 & curr, HDir dir);

	GameMove genericPlay(const GameMove & opponentsMove);
};