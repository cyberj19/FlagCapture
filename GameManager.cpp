#include "GameManager.h"
#include "Graphics.h"
#include <sstream>
#include "Utils.h"
using namespace std;

/*void printMainMenu() {
	clearScreen();
	cout << "=================Main Menu=================" << endl;
	cout << "Please make your selection" << endl;
	cout << (int)MenuOptions::SET_NAMES << " - Choose Names (Optional)" << endl;
	cout << (int)MenuOptions::REGULAR_GAME << " - Start Match" << endl;
	cout << (int)MenuOptions::SWITCHED_GAME << " - Start Match With Switched Roles" << endl;
	cout << (int)MenuOptions::RESET_SCORE << " - Reset Score" << endl;
	cout << (int)MenuOptions::TOGGLE_RECORDING << " - Enable Recording" << endl;
	cout << (int)MenuOptions::EXIT_MENU << " - Quit" << endl;
	cout << "===========================================" << endl;
	cout << "Selection: ";
}*/

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

	// show scores
}
std::string GameManager::generateMenu()
{
	stringstream menustream = stringstream();

	menustream << "=================Main Menu=================" << endl;
	menustream << "Please make your selection" << endl;
	menustream << (int)MenuOptions::SET_NAMES << " - Choose Names (Optional)" << endl;
	menustream << (int)MenuOptions::REGULAR_GAME << " - Start Match" << endl;
	menustream << (int)MenuOptions::SWITCHED_GAME << " - Start Match With Switched Roles" << endl;
	menustream << (int)MenuOptions::RESET_SCORE << " - Reset Score" << endl;

	if (!recording)
		menustream << (int)MenuOptions::TOGGLE_RECORDING << " - Enable Recording" << endl;
	else
		menustream << (int)MenuOptions::TOGGLE_RECORDING << " - Disable Recording" << endl;

	menustream << (int)MenuOptions::EXIT_MENU << " - Quit" << endl;
	menustream << "===========================================" << endl;
	menustream << "Selection: ";

	return menustream.str();
}
void GameManager::runAttended() {
	MenuOptions choice;
	do {
		 choice = (MenuOptions)show_menu(generateMenu(), 1, 9);

		switch (choice) {
		case MenuOptions::SET_NAMES:
			setUserNames();
			break;
		case MenuOptions::REGULAR_GAME:
		case MenuOptions::SWITCHED_GAME:
			startAttendedMatch(choice);
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
	} while (choice != MenuOptions::EXIT_MENU);
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
	
	printScores(UserA.getName(), UserA.getScore(), UserB.getName(), UserB.getScore());

	GameSettings settings = settingsGenerator.getNextSettings(recording);
	MatchOutput matchOutput = Match(settings).Play();

	if (matchOutput == MatchOutput::MATCH_TERMINATED) {
		announceGameStopped();
	}
	else if (matchOutput == MatchOutput::QUIT_GAME) {
		quitGame();
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
	exit(0);
}

GameManager::GameManager(GameSettingsGenerator settingsGeneator)
	: settingsGenerator(settingsGeneator), recording(false) {}
