#pragma once
#include <iostream>
#include <string>
#include "enums.h"

using namespace std;


class User {
	string name;
	int _score;
public:
	User(const string _name) :_score(0), name(_name){}
	void setName(const string _name) { name = _name; }
	void resetScore();
	void increaseScore(){ _score++; }
	int getScore() const { return _score; }
	string getName() const { return name; }
};