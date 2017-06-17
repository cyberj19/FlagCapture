#pragma once
#include "State.h"
#include <conio.h>
#include "enums.h"
#include "Input.h"
#include "GameSettings.h"
#include<string>
#include "Utils.h"
#include "AbstractPlayer.h"
#include <queue>

class State;

class KeyboardPlayer : public AbstractPlayer {
	static std::queue<char> discarded;
	std::string _layout;
	int _selectedSoldier, _selectedMove;
	int _player;
	bool _recording;
	bool _escape;
	const GameSettings& _settings;
	const BoardData* _board;
public:
	/* player: 1 for 1-2-3 player, 2 for 7-8-9 */
	virtual void setPlayer(int player) {
		_player = player;
		_layout = player == 1 ?
			_settings.getKeyboardLayoutA() : _settings.getKeyboardLayoutB();
	}
	virtual void init(const BoardData& board);
	virtual GameMove play(const GameMove& opponentsMove);
	virtual string getName() const { return _player == 1 ? "A" : "B"; }

	KeyboardPlayer(const GameSettings& settings) : 
		_settings(settings),
		_selectedSoldier(-1), _selectedMove(-1), _escape(false) {}
private:
	void processKey(char key, bool storeDiscarded);
};