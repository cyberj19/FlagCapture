#include "Match.h"
#include<stdio.h>
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Match::Match(GameSettings settings) //const char * keyboardLayoutA, const char * keyboardLayoutB)
	: _settings(settings), stage(MatchStage::INIT_DRAW), delay(settings.getDelay()), subMenu()
{
	state = new State(settings);
	graphics = new Graphics(state, _settings.isRecording());
	controller = new Controller(state, settings);

	if (settings.isAttended())
		buildSubMenu();
}

Match::~Match() {
	delete graphics;
	delete controller;
	delete state;
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
	lastSubMenuChoice = (SubMenuOptions)show_menu(subMenu, Position(11, 5), 1, 9);	
	
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


MatchOutput Match::handleEndGame() {
	controller->clearBuffer();
	if (lastSubMenuChoice == SubMenuOptions::EXIT_GAME)
		return MatchOutput::QUIT_GAME;
	else if (lastSubMenuChoice == SubMenuOptions::MAIN_MENU)
		return MatchOutput::MATCH_TERMINATED;
	else {
		if (_settings.isRecording())
			saveRecord();
		if (state->winner == Player::A)
			return MatchOutput::WINNER_A;
		else
			return MatchOutput::WINNER_B;
	}
}

void Match::saveRecord() {
	ofstream myfile;
	myfile.open(_settings.getMovesAOutputFilePath());
	myfile << state->getStepBuffer(Player::A);
	myfile.close();

	myfile.open(_settings.getMovesBOutputFilePath());
	myfile << state->getStepBuffer(Player::B);
	myfile.close();
}

void Match::buildSubMenu()
{
	subMenu.setHeader("Sub Menu");
	subMenu.setFooter("=");
	subMenu.setClearScreen(false);
	
	subMenu.addSimpleItem("Please make your selection:");
	subMenu.addFormattedSimpleItem((int)SubMenuOptions::CONTINUE_GAME, "Continue The Game");
	subMenu.addFormattedSimpleItem((int)SubMenuOptions::RESTART_GAME, "Restart The Game");
	subMenu.addFormattedSimpleItem((int)SubMenuOptions::MAIN_MENU, "Back To The Main Menu");
	subMenu.addFormattedSimpleItem((int)SubMenuOptions::EXIT_GAME, "Quit Game");
}
