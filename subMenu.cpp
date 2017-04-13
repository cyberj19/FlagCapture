#include "subMenu.h"
#include "GameManager.h"


using namespace std;


void SubMenu::runSubMenu()
{
	int choice;

	do {
		choice = getSubMenuChoice();

		switch (choice) {
			case CONTINUE_GAME:
				cout << "Continue The Game!" << endl;
				Sleep(1000);
				continueGame();
				break;
			case RESTART_GAME:
				cout << "Starting Over The Game!" << endl;
				Sleep(1000);
				restartGame();
				break;
			case MAIN_MENU:
				cout << "Returning To The Main Menu!" << endl;
				Sleep(1000);
				backToMainMenu();
				break;
			case EXIT_SUB_MENU:
				cout << "Goodbye!" << endl;
				break;
			default:
				choice = getSubMenuChoice();
		}
	} while (choice != EXIT_SUB_MENU);
	system("PAUSE");
}


const int SubMenu::getSubMenuChoice()
{
	int choice;
	clearScreen();
	cout << "=================SubMenu=================" << endl;
	cout << "Please make your selection" << endl;
	cout << CONTINUE_GAME << " - Continue The Game - " << endl;
	cout << RESTART_GAME << " - Restart Game - " << endl;
	cout << MAIN_MENU << " - Back To The Main Menu - " << endl;
	cout << EXIT_SUB_MENU << " - Quit - " << endl;
	cout << "===========================================" << endl;
	cout << "Selection: ";
	cin >> choice;
	return choice;
}

void SubMenu::continueGame()
{
	//we need to go back the game 
	//exactly from the place we have stopped
}

void SubMenu::restartGame()
{
	//reset score
	//start game
	gameManager.resetScore();
	gameManager.startMatch(); //to do: what type of game?
}

void SubMenu::backToMainMenu()
{
	//stop the game
	//show main menu again

	//gameManager.resetScore();
	gameManager.getMenuChoice();
}


