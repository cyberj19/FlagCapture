#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Controller.h"
#include "State.h"

enum class Player{A,B};

class Match{
	Graphics graphics;
	Controller controller;
	State state;
public:	
	Match(const char* keyboardLayoutA, const char* keyboardLayoutB);
	Player Play();
};