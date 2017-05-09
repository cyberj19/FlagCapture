#include "Graphics.h"
#include <time.h>
using namespace std;

#define goto_scaled_position(x, y)  (gotoxy((y)*5 + 6, (x)*2 + 3))

void Graphics::render() {
	while (state->hasChanges())
		renderChange(state->popChange());
	renderRecording();
}

void Graphics::renderChange(Position posToChange) {
	if (posToChange.getX() == -1 || posToChange.getY() == -1) return;
	goto_scaled_position(posToChange.getY(), posToChange.getX());
	const char* entity = state->getCell(posToChange).getSymbol();
	setColorByEntity(entity);
	cout << entity;
	setTextColor(WHITE, BLACK);
}

void Graphics::drawBoard()
{
	gotoxy(0, 1);
	cout << "     | A  | B  | C  | D  | E  | F  | G  | H  | I  | J  | K  | L  | M   " << endl;
	for (int i = 0; i < ROWS; i++)
	{
		hideCursor();
		cout << "-----------------------------------------------------------------------" << endl;
		printf(" %2d  ", i + 1);
		cout << "     |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;


	}
	cout << "-----------------------------------------------------------------------" << endl;
}

void Graphics::drawEnv()
{
	for (int x = 0; x < COLS; x++) {
		for (int y = 0; y < ROWS; y++) {
			const char* entity = state->getCell(x, y).getSymbol();
			goto_scaled_position(y, x);
			setColorByEntity(entity);
			cout << entity;
			setTextColor(WHITE, BLACK);
		}
	}
}

void Graphics::renderRecording()
{
	if (!_recording) return;
	gotoxy(75, 0);
	bool turnOnWidget = ((int)time(0)) % 2 == 0;
	setTextColor(RED);
	if (turnOnWidget) {
		cout << "O";
	}
	else {
		cout << " ";
	}
	cout << " REC";
	setTextColor(WHITE, BLACK);
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
	for (int i = 0; i < floor((56 - usersNamesNScoresLen) / 2.0); i++)
		cout << " ";
	setTextColor(BLUE, GREY);
	cout << "FlagCapture";
	setTextColor(DARK_RED, GREY);
	for (int i = 0; i < ceil((56 - usersNamesNScoresLen) / 2.0); i++)
		cout << " ";

	cout << userB << ": " << scoreB << endl;
	setTextColor(WHITE, BLACK);
}

void setColorByEntity(const char* entity) {
	if (!strcmp(entity, " FR ")) {
		setTextColor(WHITE, DARK_GREEN);
	}
	else if (!strcmp(entity, "SEA ")) {
		setTextColor(WHITE, DARK_BLUE);
	}
	else if ((entity[1] >= '1' && entity[1] <= '3') || (entity[0] == 'F' && entity[3] == 'A')) {
		setTextColor(RED);
	}
	else if ((entity[1] >= '7' && entity[1] <= '9') || (entity[0] == 'F' && entity[3] == 'B')) {
		setTextColor(YELLOW);
	}
	else {
		setTextColor(BLACK, WHITE);
	}
}
