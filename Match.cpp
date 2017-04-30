#include "Match.h"
#include<stdio.h>
#include "Utils.h"
void Match::handleRunning() 
{
	Input input = controller->getInput();
	if (input.action == Action::ESC) {
		stage = MatchStage::SUB_MENU;
		return;
	}
	state->step();
	Sleep(100);
	graphics->render();
	if (state->isFinished)
		stage = MatchStage::GAME_OVER;
}
void Match::handleSubMenu()
{
	lastSubMenuChoice = (SubMenuOptions)show_menu(printSubMenu, 1, 9);	
	
	switch (lastSubMenuChoice) {
	case SubMenuOptions::CONTINUE_GAME:
		stage = MatchStage::INIT_DRAW;
		break;
	case SubMenuOptions::RESTART_GAME:
		stage = MatchStage::START;
		break;
	case SubMenuOptions::MAIN_MENU:
	case SubMenuOptions::EXIT_GAME:
		stage = MatchStage::GAME_OVER;
		break;
	}
	Sleep(100);
}
void Match::handleStart()
{
	state->reset();
	controller->clearBuffer();
	stage = MatchStage::INIT_DRAW;
}

void Match::initDraw()
{
	graphics->drawBoard();
	graphics->drawEnv();

	stage = MatchStage::RUNNING;
}

Match::Match(const string keyboardLayoutA, const string keyboardLayoutB)
	: stage(MatchStage::INIT_DRAW)
{
	state = new State();

	graphics = new Graphics(state);
	controller = new Controller(state, keyboardLayoutA, keyboardLayoutB);
}

MatchOutput Match::Play()
{
	while (true) {
		switch (stage) {
		case MatchStage::START:
			handleStart();
			break;
		case MatchStage::INIT_DRAW:
			initDraw();
			break;
		case MatchStage::SUB_MENU:
			handleSubMenu();
			break;
		case MatchStage::GAME_OVER:
			return handleEndGame();
		case MatchStage::RUNNING:
		default:
			handleRunning();
			break;
		}
	}
}
