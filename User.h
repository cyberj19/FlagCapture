#pragma once
#include <iostream>
#include <string>

using namespace std;


class User {
	string name;
	int score;
public:
	User(const string _name) :score(0), name(_name){}
	void setName(const string _name) { name = _name; }
	void resetScore();
	void increaseScore(){ score++; }
	char* getKeyboardLayout();
	const int getScore() { return score; }
	const string getName() { return name; }
};