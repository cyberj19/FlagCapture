#include "Graphics.h"
#include <time.h>
using namespace std;

#define goto_scaled_position(x, y)  (gotoxy((y)*5 + 6, (x)*2 + 3))

void Graphics::render() {
	while (state->hasChanges())
		renderChange(state->popChange());
	renderRecording();
	renderClock();
}

void Graphics::renderChange(Position posToChange) {
	if (posToChange.getX() == -1 || posToChange.getY() == -1) return;
	goto_scaled_position(posToChange.getY(), posToChange.getX());
	string entity = state->getCell(posToChange).getSymbol();
	setColorByEntity(entity);
	cout << entity;
	setTextColor(WHITE, BLACK);
}

void Graphics::drawBoard()
{
	gotoxy(0, 1);
	cout << "     | A  | B  | C  | D  | E  | F  | G  | H  | I  | J  | K  | L  | M   " << endl;
	for (int i = 0; i < Board::Rows; i++){
		hideCursor();
		cout << "-----------------------------------------------------------------------" << endl;
		printf(" %2d  ", i + 1);
		cout << "     |    |    |    |    |    |    |    |    |    |    |    |    |" << endl;
	}
	cout << "-----------------------------------------------------------------------" << endl;
}

void Graphics::drawEnv()
{
	for (int x = 0; x < Board::Cols; x++) {
		for (int y = 0; y < Board::Rows; y++) {
			string entity = state->getCell(x, y).getSymbol();
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
	setTextColor(RED);
	cout << (((int)time(0)) % 2 ? " " : "O") << " REC";
	setTextColor(WHITE, BLACK);
}

void Graphics::renderClock() {
	gotoxy(75, 1);
	setTextColor(BLUE);
	cout << "Clock: " << state->getClock();
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

void printMany(int howMany, char ch) {
	for (int i = 0; i < howMany; i++)
		cout << ch;
}

int userLabelLength(User user) {
	return (int)(user.getName().length() + to_string(user.getScore()).length());
}
void printUserLabel(User user) {
	cout << user.getName() << ": " << user.getScore();
}
void printScoresHeader(User userA, User userB) {
	clearScreen();

	int usersNamesNScoresLen = userLabelLength(userA) + userLabelLength(userB);

	gotoxy(0, 0);
	setTextColor(DARK_RED, GREY);
	printUserLabel(userA);
	printMany((int) floor((56 - usersNamesNScoresLen) / 2.0), ' ');
	setTextColor(BLUE, GREY);
	cout << "FlagCapture";
	setTextColor(DARK_RED, GREY);
	printMany((int) ceil((56 - usersNamesNScoresLen) / 2.0), ' ');
	printUserLabel(userB);
	setTextColor(WHITE, BLACK);
}

void setColorByEntity(string entity) {
	if (entity == " FR ") {
		setTextColor(WHITE, DARK_GREEN);
	}
	else if (entity == "SEA ") {
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


void showFinalResults(User userA, User userB, bool isQuiet) {
	if(!isQuiet) 
		clearScreen();

	cout << "Game summary: " << endl;
	cout << "A points: " << userA.getScore() << endl;
	cout << "B points: " << userB.getScore() << endl;

	cout << "Press any key to continue..." << endl;
	_getch();
}

void showMatchResults(int round, int numMoves, MatchOutput result)
{
	cout << "Game cycle: " << round << endl;
	cout << "Num moves: " << numMoves << endl;
	cout << "Winner: " <<
		(result == MatchOutput::WINNER_A ? "A" :
		result == MatchOutput::WINNER_B ? "B" : "NONE") << endl;
	cout << "----------------------" << endl;
}


void showErrors(vector<string> errors, bool isQuiet) {
	if (!isQuiet)
		clearScreen();
	cout << "Errors while loading game: " << endl;
	for (string & error : errors)
		cout << error << endl;
	
	if (!isQuiet) {
		cout << "Press any key to continue..." << endl;
		_getch();
	}
}