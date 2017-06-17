#pragma once
#include <iostream>
#include <string>
#include "enums.h"
#include "AbstractPlayer.h"

class User {
	std::string _name;
	int _score;
	AbstractPlayer* _player;
public:
	User(const std::string& name) : _score(0), _name(name){}

	void setName(const std::string& name) { _name = name; }
	void setPlayer(AbstractPlayer* player) {
		_player = player;
		_name = player->getName();
	}


	void resetScore();
	void increaseScore();
	

	AbstractPlayer* getPlayer() const { return _player; }
	int getScore() const { return _score; }
	std::string getName() const { return _name; }
};