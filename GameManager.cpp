#include "GameManager.h"
#include "Graphics.h"
#include <sstream>
#include "Utils.h"
using namespace std;

void printMainMenu() {
	clearScreen();
	cout << "=================Main Menu=================" << endl;
	cout << "Please make your selection" << endl;
	cout << (int)MenuOptions::SET_NAMES << " - Choose Names (Optional)" << endl;
	cout << (int)MenuOptions::REGULAR_GAME << " - Start Match" << endl;
	cout << (int)MenuOptions::SWITCHED_GAME << " - Start Match With Switched Roles" << endl;
	cout << (int)MenuOptions::RESET_SCORE << " - Reset Score" << endl;
	cout << (int)MenuOptions::EXIT_MENU << " - Quit" << endl;
	cout << "===========================================" << endl;
	cout << "Selection: ";
}
void GameManager::run() {
	MenuOptions choice;
	do {
		 choice = (MenuOptions)show_menu(printMainMenu, 1, 9);

		switch (choice) {
		case MenuOptions::SET_NAMES:
			setUserNames();
			break;
		case MenuOptions::REGULAR_GAME:
			startMatch(MenuOptions::REGULAR_GAME);
			break;
		case MenuOptions::SWITCHED_GAME:
			startMatch(MenuOptions::SWITCHED_GAME);
			break;
		case MenuOptions::RESET_SCORE:
			resetScore();
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
	/*int in = _kbhit();
	while (in) {
		_getch();
		in = _kbhit();
	}*/
	cin >> user_A_name;
	cout << "Please Enter a Name for User B\n";
	/*in = _kbhit();
	while (in) {
		_getch();
		in = _kbhit();
	}*/
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
void GameManager::startMatch(MenuOptions GameType) {
	
	printScores(UserA.getName(), UserA.getScore(), UserB.getName(), UserB.getScore());
	/*const char *akeys = GameType == MenuOptions::REGULAR_GAME ? 
		DEFAULT_PLAYER_A_KEY_LAYOUT : DEFAULT_PLAYER_B_KEY_LAYOUT;
	const char *bkeys = GameType == MenuOptions::REGULAR_GAME ?
		DEFAULT_PLAYER_B_KEY_LAYOUT : DEFAULT_PLAYER_A_KEY_LAYOUT;*/
	Match match = Match(DEFAULT_PLAYER_A_KEY_LAYOUT, DEFAULT_PLAYER_B_KEY_LAYOUT);
	MatchOutput matchOutput = match.Play();

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
