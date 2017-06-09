﻿#pragma once
#include "Match.h"
#include<stdio.h>
#include "Utils.h"
#include "Graphics.h"
#include "StateProxy.h"
#include "State.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Match::Match()
	: 
	_settings(),
	stage(MatchStage::START), 
	subMenu(),
	_errors(),
	error(false),
	state(nullptr),
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
	proxyA = new StateProxy(state, Player::A);
	proxyB = new StateProxy(state, Player::B);

	playerA = _settings.getPlayerA();
	playerA->init(*proxyA);
	playerB = _settings.getPlayerB();
	playerB->init(*proxyB);
	if (!_settings.isQuiet()) {
		graphics = new Graphics(state, _settings.isRecording());
		buildSubMenu();
	}

	return true;
}

int Match::getLastClock()
{
	return state->getClock();
}

Match::~Match() {
	if (graphics != nullptr)
		delete graphics;
	if (playerA != nullptr)
		delete playerA;
	if (playerB != nullptr)
		delete playerB;
	if (proxyA != nullptr)
		delete proxyA;
	if (proxyB != nullptr)
		delete proxyB;
	if (state != nullptr)
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

void Match::applyLastMove() {
	state->step(lastMove);
	if (!_settings.isQuiet())
	{
		Sleep(_settings.getDelay());
		graphics->render();
	}
}
void Match::handleRunning() 
{
	lastMove = playerA->play(lastMove);
	applyLastMove();

	if (state->isFinished)
	{
		stage = MatchStage::GAME_OVER;
		return;
	}

	lastMove = playerB->play(lastMove);
	applyLastMove();

	if (state->isFinished)
	{
		stage = MatchStage::GAME_OVER;
		return;
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
	return MatchOutput::WINNER_A;
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
