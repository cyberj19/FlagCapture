#include <iostream>

using namespace std;

class Game {

};

class PlayerA {
	//To do:
	//Player has 3 tools
	//We need to set their positions: Random positions lines 1-5
	//Every tool has properties

};

class PlayerB {
	//To do:
	//Player has 3 tools
	//We need to set their positions: Random positions lines 9-13
	//Every tool has properties
};

void gameMainMenu() {

	Game menu;
	int choice;
	bool flag;


	do
	{
		flag = 1;

		cout << "Welcome to our game!" << endl;
		cout << "Please choose one of the following options: " << endl;
		cout << " 1  - Select Players' names: first for player A, then for player B: " << endl;
		cout << " 2 - Start a game" << endl;
		cout << " 3 - Start a reverse game" << endl;
		cout << " 4 - Reset score" << endl;
		cout << " 9 - Quit " << endl;

		cin >> choice;

		switch (choice)
		{
			case 1: menu.setPlayersNames();
				break;
			case 2: menu.Play();
				break;
			case 3: menu.PlayRevers();
				break;
			case 4: menu.resetScore();
				break;
			case 9: Quit();
				break;
			default:
				flag = 0;
				cout << "\nSorry, but " << choice << " isn't a valid choice.\n";
				break;
		}

	} while (!flag);
}



int main()
{
	Game game;
	game.Run();
}