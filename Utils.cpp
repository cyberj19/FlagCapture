#include "Utils.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <iterator>
using namespace std;

int showMenu(Menu& menu, Position_203398664 pos, int minChoice, int maxChoice)
{
	string input;
	int choice = minChoice - 1;
	do {
		menu.printAtPosition(pos.getX(), pos.getY());

		// this allows only valid integer inputs
		while (_kbhit()) _getch();
		getline(cin, input);
		stringstream mstream(input);
		if (!(mstream >> choice))
			choice = minChoice - 1;
	} while (choice < minChoice || choice > maxChoice);
	return choice;
}

void setTextColor(int foreground_color, int background_color) {
	int color = foreground_color | background_color * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setTextColor(int foreground_color) {
	setTextColor(foreground_color, 0);
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


vector<string> split(string input, string delims) {
	vector<string> output = vector<string>();
	string word;
	char c;

	stringstream stream = stringstream(input);

	c = stream.get();
	while (stream) {
		word.clear();
		while (c != EOF && delims.find(c) == string::npos) {
			word.push_back(c);
			c = stream.get();
		}

		if (!word.empty()) output.push_back(word);
		while (c != EOF && delims.find(c) != string::npos) {
			c = stream.get();
		}
	}

	return output;
}

std::string stripExtension(const std::string & file){
	return file.substr(0, file.find_last_of('.'));
}


void trim(string& str) {
	size_t endpos = str.find_last_not_of(" \t\r\n");
	if (string::npos != endpos)
		str = str.substr(0, endpos + 1);

	size_t startpos = str.find_first_not_of(" \t\r\n");
	if (string::npos != startpos)
		str = str.substr(startpos);
}

void trim(vector<string>& strings) {
	for (string& str : strings)
		trim(str);
}