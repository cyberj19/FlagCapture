#pragma once
#include <iostream>
#include <string>
#include "enums.h"

using namespace std;


class User {
	string name;
	int score;
public:
	User(const string _name) :score(0), name(_name){}
	void setName(const string _name) { name = _name; }
	void resetScore();
	void increaseScore(){ score++; }
	const int getScore() { return score; }
	const string getName() { return name; }
	//TO DO:
	//The function doesn't change the data member
	//we need to change it in every "get" function
	//int getScore() const { return score; }
	//string getName() const { return name; }
};
