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
		setTextColor(WHITE, BLACK);
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
	gotoxy(posToChange.y * 5 + 6, posToChange.x * 2 + 2);
	const char* entity = state->getCell(Position(posToChange.x, posToChange.y)).getSymbol();
	setColorByEntity(entity);
	cout << state->getCell(posToChange).getSymbol();
	setTextColor(WHITE, BLACK);
}

void Graphics::drawBoard()
{
	clearScreen();
	//cout << "-----------------------------------------------------------------------" << endl;
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
	}
	cout << "-----------------------------------------------------------------------" << endl;
	//cout << "Scores: " << userA << ": X                    " << userB << ":  Y" << endl;
}

void Graphics::drawEnv()
{
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLS; j++){
			const char* entity = state->getCell(Position(i, j)).getSymbol();
			gotoxy(j * 5 +6, i * 2 + 2);
			setColorByEntity(entity);
			cout << entity;
			setTextColor(WHITE, BLACK);
		}
	}
}

void announceWinner(string winner)
{
	clearScreen();
	cout << "The winner is " << winner << endl;
	Sleep(2000);
}
