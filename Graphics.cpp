#include "Graphics.h"

using namespace std;

void setTextColor(int foreground_color, int background_color) {
	int color = foreground_color | background_color * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setTextColor(int foreground_color) {
	setTextColor(foreground_color, 0);
}

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
		setTextColor(RED, BLACK);
	}
	else{
		setTextColor(BLACK, OLIVE);
	}
}

void clearScreen() {
	system("cls");
}

// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}


void Graphics::render() {
	renderChange(state->getChanges(0));
	renderChange(state->getChanges(1));
}

void Graphics::renderChange(Position posToChange) {
	if (posToChange.x == -1 || posToChange.y == -1) return;
	gotoxy(posToChange.y * 5 + 6, posToChange.x * 2 + 3);
	const char* entity = state->getCell(Position(posToChange.x, posToChange.y)).getSymbol();
	setColorByEntity(entity);
	cout << state->getCell(posToChange).getSymbol();
	setTextColor(WHITE, BLACK);
}

void Graphics::drawBoard()
{
	setTextColor(BLACK, GREY);
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
			gotoxy(j * 5 +6, i * 2 + 3);
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
