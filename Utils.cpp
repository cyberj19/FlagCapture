#include "Utils.h"
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <iostream>
using namespace std;

int show_menu(string menu, int minChoice, int maxChoice)
{
	string input;
	int choice = minChoice - 1;
	do {
		clearScreen();
		cout << menu;
		while (_kbhit()) _getch();
		getline(cin, input);
		stringstream mstream(input);
		if (!(mstream >> choice))
			choice = minChoice - 1;
	} while (choice < minChoice || choice > maxChoice);
	return choice;
}
int show_menu(void (*printMenu)(void), int minChoice, int maxChoice)
{
	string input;
	int choice = minChoice - 1;
	do {
		printMenu();
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