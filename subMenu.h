#include "GameManager.h"



class SubMenu
{
	GameManager gameManager;

	const int getSubMenuChoice();
	void continueGame();
	void restartGame(int gameType);
	void backToMainMenu();

public:
	void runSubMenu();
}