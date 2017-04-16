#include "Graphics.h"

using namespace std;

#define goto_scaled_position(x, y)  (gotoxy((y)*5 + 6, (x)*2 + 3))


void setColorByEntity(const char* entity) {
	if (!strcmp(entity, " FR ")) {
		setTextColor(WHITE, DARK_GREEN);
	}
	else if (!strcmp(entity, "SEA ")) {
		setTextColor(WHITE, DARK_BLUE);
	}
	else if (entity[0] == 'F') { // if it's a flag cell
		setTextColor(YELLOW, BLACK);
	}
	else if (entity[1] >= '1' && entity[1] <= '9') {
		setTextColor(RED);
	}
	else{
		setTextColor(BLACK, WHITE);
	}
}




void Graphics::render() {
	renderChange(state->getChanges(0));
	renderChange(state->getChanges(1));
}

void Graphics::renderChange(Position posToChange) {
	if (posToChange.x == -1 || posToChange.y == -1) return;
	goto_scaled_position(posToChange.x, posToChange.y);
	const char* entity = state->getCell(posToChange).getSymbol();
	setColorByEntity(entity);
	cout << entity;
	setTextColor(WHITE, BLACK);
}

void Graphics::drawBoard()
{
	setTextColor(BLACK, GREY);
	gotoxy(0, 1);
	cout << "     | A  | B  | C  | D  | E  | F  | G  | H  | I  | J  | K  | L  | M   " << endl;
	setTextColor(WHITE, BLACK);
	for (int i = 0; i < ROWS; i++)
	{
		hideCursor();
		cout << "-----------------------------------------------------------------------" << endl;
		setTextColor(BLACK, GREY);
		printf(" %2d  ", i + 1); 
		setTextColor(WHITE, BLACK);
		cout << "     |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
		setTextColor(BLACK, OLIVE);
		//cout << "                                                                  " << endl;
		setTextColor(WHITE, BLACK);

	}
	cout << "-----------------------------------------------------------------------" << endl;
}

void Graphics::drawEnv()
{
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLS; j++){
			const char* entity = state->getCell(Position(i, j)).getSymbol();
			goto_scaled_position(i, j);
			setColorByEntity(entity);
			cout << entity;
			setTextColor(WHITE, BLACK);
		}
	}
}

void announceWinner(string winner)
{
	gotoxy(0, 29);
	cout << "The winner is " << winner << endl;
	Sleep(2000);
}

void announceGameStopped()
{
	gotoxy(0, 29);
	cout << "Game was stopped" << endl;
	Sleep(2000);
}

void printScores(string userA, int scoreA, string userB, int scoreB) {
	clearScreen();

	gotoxy(0, 0);
	setTextColor(DARK_RED, GREY);
	cout << userA << ": " << scoreA;
	int usersNamesNScoresLen = userA.length() + userB.length() + (to_string(scoreA)).length() + (to_string(scoreB)).length();
	for (int i = 0; i < floor((56 - usersNamesNScoresLen)/2.0); i++)
		cout << " ";
	setTextColor(BLUE, GREY);
	cout << "FlagCapture";
	setTextColor(DARK_RED, GREY);
	for (int i = 0; i < ceil((56 - usersNamesNScoresLen) / 2.0); i++)
		cout << " ";

	cout <<userB << ": " << scoreB << endl;
	setTextColor(WHITE, BLACK);
}

void printSubMenu() {
	gotoxy(11, 5);
	cout <<                                              "=================SubMenu=================" << endl;
	gotoxy(11, 6);
	cout << "||" <<                                      " Please make your selection          ||" << endl;
	gotoxy(11, 7);
	cout << "||" << (int)SubMenuOptions::CONTINUE_GAME << " - Continue The Game -              ||" << endl;
	gotoxy(11, 8);
	cout << "||" << (int)SubMenuOptions::RESTART_GAME  << " - Restart Game -                   ||" << endl;
	gotoxy(11, 9);
	cout << "||" << (int)SubMenuOptions::MAIN_MENU     << " - Back To The Main Menu -          ||" << endl;
	gotoxy(11, 10);
	cout << "||" << (int)SubMenuOptions::EXIT_GAME     << " - Quit Game -                      ||" << endl;
	gotoxy(11, 11);
	cout <<                                              "=========================================" << endl;
	gotoxy(11, 12);
	cout << "Selection:                               ";
	gotoxy(22, 12);
}
