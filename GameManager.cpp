#include "GameManager.h"
#include "Graphics.h"

using namespace std;

void GameManager::run() {
	int choice;

	do {
		choice = getMenuChoice();

		switch (choice) {
		case SET_NAMES:
			cout << "Setting User Name!" << endl;
			Sleep(1000);
			setUserNames();
			break;
		case REGULAR_GAME:
			cout << "Starting Regular Game!" << endl;
			Sleep(1000);
			startMatch(REGULAR_GAME);
			break;
		case SWITCHED_GAME:
			cout << "Starting Switched Game!" << endl;
			Sleep(1000);
			startMatch(SWITCHED_GAME);
			break;
		case RESET_SCORE:
			cout << "reset score!" << endl;
			Sleep(1000);
			resetScore();
			break;
		case EXIT_MENU:
			cout << "Goodbye!" << endl;
			break;
		default:
			choice = getMenuChoice();
		}
	} while (choice != EXIT_MENU);
	system("PAUSE");
}

int GameManager::getMenuChoice() {
	int choice;
	clearScreen();
	cout << "=================Main Menu=================" << endl;
	cout << "Please make your selection" << endl;
	cout << SET_NAMES << " - Choose Names (Optional)" << endl;
	cout << REGULAR_GAME << " - Start Match" << endl;
	cout << SWITCHED_GAME << " - Start Match With Switched Roles" << endl;
	cout << RESET_SCORE << " - Reset Score" << endl;
	cout << EXIT_MENU << " - Quit" << endl;
	cout << "===========================================" << endl;
	cout << "Selection: ";
	cin >> choice;
	return choice;
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

void GameManager::startMatch(int GameType) {
	Player winner;
	if (GameType == REGULAR_GAME) {
		Match match = Match("123wxad", "789imjl");
		winner = match.Play();
		if (winner == Player::A) {
			UserA.increaseScore();
			announceWinner(UserA.getName());
		}
		else {
			UserB.increaseScore();
			announceWinner(UserB.getName());
		}
	}
	else if (GameType == SWITCHED_GAME) {
		Match match = Match("789imjl", "123wxad");
		winner = match.Play();
		if (winner == Player::B) {
			UserA.increaseScore();
			announceWinner(UserA.getName());
		}
		else {
			UserB.increaseScore();
			announceWinner(UserB.getName());
		}
	}
}