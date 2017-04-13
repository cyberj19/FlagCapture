#pragma once
#include <Windows.h>
#include "Graphics.h"
#include "Controller.h"
#include "State.h"
#include "enums.h"

class State;
class Controller;
class Graphics;

class Match{
	Graphics *graphics;
	Controller *controller;
	State *state;
public:	
	Match(const char* keyboardLayoutA, const char* keyboardLayoutB);
	Player Play();
};