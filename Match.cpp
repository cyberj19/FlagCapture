#pragma once
#include "Match.h"
#include<stdio.h>
#include "Utils.h"
#include "Graphics.h"
#include "Controller.h"
#include "State.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Match::Match()
	: 
	_settings(),
	stage(MatchStage::INIT_DRAW), 
	subMenu(),
	_errors(),
	error(false),
	state(nullptr),
	controller(nullptr),
	graphics(nullptr)
{
}

bool Match::load(GameSettings settings) {
	_settings = settings;
	BoardConfiguration config = BoardConfiguration();
	if (!config.loadSettings(_settings)) {
		error = true;
		_errors = config.getErrors();
		return false;
	}

	state = new State(_settings, config);
	controller = new Controller(state, _settings);

	if (!_settings.isQuiet()) {
		graphics = new Graphics(state, _settings.isRecording());
		buildSubMenu();
	}

	return true;
}

int Match::getNumMoves()
{
	return controller->getNumMoves();
}

Match::~Match() {
	if (graphics != nullptr)
		delete graphics;
	if (controller != nullptr)
		delete controller;	
	if (state != nullptr)
		delete state;	
}

MatchOutput Match::Play()
{
	if (error) return MatchOutput::MATCH_TERMINATED;
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
	if (input.getAction() == Action::ESC) {
		stage = MatchStage::SUB_MENU;
		return;
	}
	state->step();
	Sleep(_settings.getDelay());

	if (!_settings.isQuiet())
		graphics->render();

	if (state->isFinished)
		stage = MatchStage::GAME_OVER;
	else if (controller->eof() && !state->anyMoving()) {
		stage = MatchStage::GAME_OVER;
		lastSubMenuChoice = SubMenuOptions::EXIT_GAME;
	}
		
}

void Match::handleSubMenu()
{
	lastSubMenuChoice = (SubMenuOptions)showMenu(subMenu, Position(11, 5), 1, 9);	
	
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
	if (!_settings.isQuiet()) {
		graphics->drawBoard();
		graphics->drawEnv();
	}
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
			saveMatch();
		if (state->winner == Player::A)
			return MatchOutput::WINNER_A;
		else
			return MatchOutput::WINNER_B;
	}
}

void writeToFile(string str, string file) {
	ofstream hfile;
	hfile.open(file);
	hfile << str;
	hfile.close();
}

void Match::saveMatch() {
	writeToFile(state->getStepBuffer(Player::A), _settings.getMovesAOutputFilePath());
	writeToFile(state->getStepBuffer(Player::B), _settings.getMovesBOutputFilePath());
	writeToFile(state->getBoardString(), _settings.getBoardOutputFilePath());
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
