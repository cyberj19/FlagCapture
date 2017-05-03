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
	Sleep(delay);
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

Match::Match(GameSettings settings) //const char * keyboardLayoutA, const char * keyboardLayoutB)
	: stage(MatchStage::INIT_DRAW), delay(100)
{
	state = new State(settings);
	graphics = new Graphics(state);
	controller = new Controller(state, settings);
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

MatchOutput Match::handleEndGame() {
	controller->clearBuffer();
	if (lastSubMenuChoice == SubMenuOptions::EXIT_GAME)
		return MatchOutput::QUIT_GAME;
	else if (lastSubMenuChoice == SubMenuOptions::MAIN_MENU)
		return MatchOutput::MATCH_TERMINATED;
	else if (state->winner == Player::A)
		return MatchOutput::WINNER_A;
	else
		return MatchOutput::WINNER_B;
}