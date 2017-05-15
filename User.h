#pragma once
#include <iostream>
#include <string>
#include "enums.h"

using namespace std;


class User {
	std::string _name;
	int _score;
public:
	User(const std::string& name) : _score(0), _name(name){}
	void setName(const std::string& name) { _name = name; }
	void resetScore();
	void increaseScore();
	const int getScore() { return _score; }
	const string getName() { return _name; }
};