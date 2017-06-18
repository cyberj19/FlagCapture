#pragma once
#include "GameManager.h"
#include "Graphics.h"
#include <sstream>
#include "Utils.h"
#include "AlgorithmRegistration.h"
using namespace std;

void GameManager::run() {
	switch (settingsGenerator.getGameType()) {
	case GameType::Attended:
		runAttendedGame();
		break;
	case GameType::FileGame:
		runFileGame();
		break;
	case GameType::AlgorithmGame:
	default:
		runAlgorithmGame();
	}
}


void GameManager::runFileGame() {
	while (settingsGenerator.moreSettings())
		startMatch(settingsGenerator.getNextSettings(false, ++_round));
	showFinalResults(UserA, UserB, settingsGenerator.isQuiet());
}

void GameManager::buildMenu(){
	gameMenu.setHeader("Main Menu");
	gameMenu.setFooter("=");
	gameMenu.setClearScreen(true);	
	gameMenu.addSimpleItem("Please make your selection:");
	gameMenu.addFormattedSimpleItem((int) MenuOptions::SET_NAMES, "Choose names (optional)");
	gameMenu.addFormattedSimpleItem((int)MenuOptions::REGULAR_GAME, "Start Match");
	gameMenu.addFormattedSimpleItem((int)MenuOptions::SWITCHED_GAME, "Start Match With Switched Roles");
	gameMenu.addFormattedSimpleItem((int)MenuOptions::RESET_SCORE, "Reset Score");
	gameMenu.addFormattedToggledItem((int)MenuOptions::TOGGLE_RECORDING, "Disable Recording",
		"Enable Recording", &recording);
	gameMenu.addFormattedSimpleItem((int)MenuOptions::EXIT_MENU, "Quit");
}

void GameManager::runAttendedGame() {
	do {
		 _lastChoice = (MenuOptions)showMenu(gameMenu, Pos203398664(0, 0), 1, 9);

		switch (_lastChoice) {
		case MenuOptions::SET_NAMES:
			setUserNames();
			break;
		case MenuOptions::REGULAR_GAME:
		case MenuOptions::SWITCHED_GAME:
			startAttendedMatch(_lastChoice);
			break;
		case MenuOptions::RESET_SCORE:
			resetScore();
			break;
		case MenuOptions::TOGGLE_RECORDING:
			recording = !recording;
			break;
		case MenuOptions::EXIT_MENU:
		default:
			break;
		}
	} while (_lastChoice != MenuOptions::EXIT_MENU);
	quitGame();
}

void initiatePlayer(User& user, const GameSettings& settings, InputOptions playerType, Player playerId) {
	int playerIdx = playerId == Player::A ? 1 : 2;

	AbstractPlayer* player;
	if (playerType == InputOptions::Algorithm)
		player = AlgorithmRegistration::nextAlgorithm();
	else if (playerType == InputOptions::FromFile)
		player = new FilePlayer(settings);
	else
		player = new KeyboardPlayer(settings);

	player->setPlayer(playerIdx);
	user.setPlayer(player);
}

void GameManager::initiatePlayers(const GameSettings& settings) {
	initiatePlayer(UserA, settings, settings.getInputOptionA(), Player::A);
	initiatePlayer(UserB, settings, settings.getInputOptionB(), Player::B);
}
void GameManager::deallocatePlayers()
{
	delete UserA.getPlayer();
	delete UserB.getPlayer();
}
void GameManager::runAlgorithmGame() {
	while (settingsGenerator.moreSettings())
		startMatch(settingsGenerator.getNextSettings(false, ++_round));
	showFinalResults(UserA, UserB, settingsGenerator.isQuiet());
}
void GameManager::setUserNames() {
	string user_A_name, user_B_name;
	clearScreen();
	cout << "================Choose Names================\n";
	cout << "Please Enter a Name for User A\n";
	cin >> user_A_name;
	cout << "Please Enter a Name for User B\n";
	cin >> user_B_name;
	UserA.setName(user_A_name);
	UserB.setName(user_B_name);
}

void GameManager::resetScore()
{
	UserA.resetScore();
	UserB.resetScore();
}

User& GameManager::getWinningUser(MenuOptions GameType, MatchOutput matchOutput) {
	if (GameType == MenuOptions::REGULAR_GAME)
		return matchOutput == MatchOutput::WINNER_A ? UserA : UserB;
	else
		return matchOutput == MatchOutput::WINNER_B ? UserA : UserB;
}


void GameManager::startMatch(const GameSettings &settings, MenuOptions GameType) {
	initiatePlayers(settings);
	Match match = Match();
	if (!match.load(settings, UserA.getPlayer(), UserB.getPlayer())) {
		showErrors(match.getErrors(), settings.isQuiet());
		return;
	}

	if (!settings.isQuiet())
		printScoresHeader(UserA, UserB);

	MatchOutput matchOutput = match.Play();

	if (matchOutput == MatchOutput::MATCH_TERMINATED && !settings.isQuiet())
		announceGameStopped();
	else if (matchOutput == MatchOutput::QUIT_GAME)
		_lastChoice = MenuOptions::EXIT_MENU;
	else if (matchOutput == MatchOutput::TIE) {
		UserA.increaseScore();
		UserB.increaseScore();
		if (!settings.isQuiet())
			announceTie();
	}
	else {
		User &winnerUser = getWinningUser(GameType, matchOutput);
		winnerUser.increaseScore();

		if (!settings.isQuiet())
			announceWinner(winnerUser.getName());
	}

	if (settings.isQuiet())
		showMatchResults(_round, match.getLastClock(), matchOutput);
	else if (settings.getGameType() != GameType::Attended)
		Sleep(50 * settings.getDelay());
	deallocatePlayers();
}
void GameManager::startAttendedMatch(MenuOptions GameType) {
	++_round;
	GameSettings settings = settingsGenerator.getNextSettings(recording, _round);
	startMatch(settings, GameType);
}

void GameManager::quitGame()
{
	clearScreen();
	cout << "Goodbye!";
	Sleep(1000);
}

GameManager::GameManager(GameSettingsGenerator settingsGeneator)
	: settingsGenerator(settingsGeneator), recording(false), gameMenu(), _round(0), UserA("A"), UserB("B") 
{
	if (settingsGenerator.getGameType() == GameType::Attended)
		buildMenu();
}
