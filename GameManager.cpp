#include "GameManager.h"
#include "Graphics.h"
#include <sstream>
#include "Utils.h"
using namespace std;

void GameManager::run() {
	if (settingsGenerator.isAttended())
		runAttended();
	else
		runUnattended();
}

void GameManager::runUnattended() {
	while (settingsGenerator.moreSettings()) {
		GameSettings settings = settingsGenerator.getNextSettings(false);
		MatchOutput matchOutput = Match(settings).Play();

		if (matchOutput == MatchOutput::WINNER_A) UserA.increaseScore();
		else UserB.increaseScore();
	}

	// TODO: show scores
}
void GameManager::buildMenu()
{
	gameMenu.setHeader("Main Menu");
	gameMenu.setFooter("=");
	gameMenu.setClearScreen(true);
	stringstream menustream = stringstream();
	
	gameMenu.addSimpleItem("Please make your selection:");
	
	menustream << (int)MenuOptions::SET_NAMES << " - Choose Names (Optional)";
	gameMenu.addSimpleItem(menustream.str());
	menustream.str(std::string());

	menustream << (int)MenuOptions::REGULAR_GAME << " - Start Match";
	gameMenu.addSimpleItem(menustream.str());
	menustream.str(std::string());

	menustream << (int)MenuOptions::SWITCHED_GAME << " - Start Match With Switched Roles";
	gameMenu.addSimpleItem(menustream.str());
	menustream.str(std::string());

	menustream << (int)MenuOptions::RESET_SCORE << " - Reset Score";
	gameMenu.addSimpleItem(menustream.str());
	menustream.str(std::string());

	menustream << (int)MenuOptions::TOGGLE_RECORDING << " - Enable Recording";
	string temp = menustream.str();
	menustream.str(std::string());
	menustream << (int)MenuOptions::TOGGLE_RECORDING << " - Disable Recording";
	gameMenu.addToggledItem(menustream.str(), temp, &recording);
	menustream.str(std::string());

	menustream << (int)MenuOptions::EXIT_MENU << " - Quit";
	gameMenu.addSimpleItem(menustream.str());
	menustream.str(std::string());

}
void GameManager::runAttended() {
	do {
		 _lastChoice = (MenuOptions)show_menu(gameMenu, Position(0, 0), 1, 9);

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
void GameManager::startAttendedMatch(MenuOptions GameType) {
	++_round;
	printScores(UserA.getName(), UserA.getScore(), UserB.getName(), UserB.getScore());

	GameSettings settings = settingsGenerator.getNextSettings(recording, _round);
	MatchOutput matchOutput = Match(settings).Play();

	if (matchOutput == MatchOutput::MATCH_TERMINATED) {
		announceGameStopped();
	}
	else if (matchOutput == MatchOutput::QUIT_GAME) {
		_lastChoice = MenuOptions::EXIT_MENU;
	}
	else {
		User &winnerUser = getWinningUser(GameType, matchOutput);
		winnerUser.increaseScore();
		announceWinner(winnerUser.getName());
	}
}

void GameManager::quitGame()
{
	clearScreen();
	cout << "Goodbye!";
	Sleep(1000);
}

GameManager::GameManager(GameSettingsGenerator settingsGeneator)
	: settingsGenerator(settingsGeneator), recording(false), gameMenu(), _round(0) {
	buildMenu();
}
