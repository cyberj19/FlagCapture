#include <Windows.h>
#include <conio.h>
#include "GameManager.h"
#include <iostream>
#include "User.h"



enum MenuOptions{ SET_NAMES = 1, REGULAR_GAME = 2, SWITCHED_GAME = 3, RESET_SCORE = 4, EXIT_MENU = 9 };

using namespace std;

void GameManager::run() {
	int choice;

	do {
		choice = getMenuChoice();

		switch (choice) {
		case SET_NAMES:
			cout << "Setting User Name!\n";
			setUserNames();
			break;
		case REGULAR_GAME:
			cout << "Starting Regular Game!\n";
			Sleep(1000);
			startMatch(REGULAR_GAME);
			break;
		case SWITCHED_GAME:
			cout << "Starting Switched Game!\n";
			Sleep(1000);
			startMatch(SWITCHED_GAME);
			break;
		case RESET_SCORE:
			cout << "reset score!";
			resetScore();
			break;
		case EXIT_MENU:
			cout << "Goodbye!";
			break;
		default:
			choice = getMenuChoice();
		}
	} while (choice != EXIT_MENU);
	system("PAUSE");
}

int GameManager::getMenuChoice() {
	int choice;
	cout << "Main Menu\n";
	cout << "Please make your selection\n";
	cout << SET_NAMES << " - Choose Names (Optional)\n";
	cout << REGULAR_GAME << " - Start Match\n";
	cout << SWITCHED_GAME << " - Start Match With Switched Roles\n";
	cout << RESET_SCORE << " - Reset Score\n";
	cout << EXIT_MENU << " - Quit\n";
	cout << "Selection: ";
	cin >> choice;
	return choice;
}
void GameManager::setUserNames() {
	string user_A_name, user_B_name;
	cout << "Choose Names\n";
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

void GameManager::startMatch(int GameType) {
	Player winner;
	if (GameType == REGULAR_GAME) {
		Match match = Match(UserA.getKeyboardLayout(), UserB.getKeyboardLayout());
		winner = match.Play();
		if (winner == Player::A) {
			UserA.increaseScore();
		}
		else {
			UserB.increaseScore();
		}
	}
	else if (GameType == SWITCHED_GAME) {
		Match match = Match(UserB.getKeyboardLayout(), UserA.getKeyboardLayout());
		winner = match.Play();
		if (winner == Player::B) {
			UserA.increaseScore();
		}
		else {
			UserB.increaseScore();
		}
	}
}