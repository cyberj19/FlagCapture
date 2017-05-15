#pragma once
#include "Menu.h"
#include <iostream>
#include <sstream>
#include "Utils.h"
using namespace std;

void Menu::addSimpleItem(string label) {
	menuItems.push_back(MenuItem(label));
}

void Menu::addToggledItem(string labelIfTrue, string labelIfFalse, bool *bind)
{
	menuItems.push_back(MenuItem(labelIfTrue, labelIfFalse, bind));
}


void Menu::printAtPosition(int x, int y) {
	string pleaseSelect = "Please Select: ";
	int maxLine = (int) max(_header.length(), _footer.length());
	maxLine = max(maxLine, (int) pleaseSelect.length() + 5);

	vector<string> itemStrings = vector<string>();
	for (auto& item : menuItems) {
		string itemString = item.format();
		maxLine = (int) max(maxLine, itemString.length() + 5);
		itemStrings.push_back(item.format());
	}

	if (_clearScreen) clearScreen();
	printHeader(x, y++, maxLine);
	printItems(itemStrings, x, y, maxLine); y += (int) itemStrings.size();
	printString(pleaseSelect, x, y, maxLine); y++;
	printFooter(x, y, maxLine);
	gotoxy(x + (int) pleaseSelect.length() + 2, y - 1);
}

void Menu::printString(string str, int x, int y, int maxLine) {
	gotoxy(x, y);
	printPaddedString(str, maxLine, Alignment::LEFT, ' ', true);
}

void Menu::printHeader(int x, int y, int maxLine)
{
	if (_header != "") {
		gotoxy(x, y);
		printPaddedString(_header, maxLine, Alignment::CENTER, '=', false);
	}
}

void Menu::printItems(vector<string>& itemStrings, int x, int y, int maxLine)
{
	if (!itemStrings.empty()) {
		for (auto item : itemStrings) {
			gotoxy(x, y);
			printPaddedString(item, maxLine, Alignment::LEFT, ' ', true);
			++y;
		}
	}
}

void Menu::printFooter(int x, int y, int maxLine)
{
	if (_footer != "") {
		gotoxy(x, y);
		printPaddedString(_footer, maxLine, Alignment::CENTER, '=', false);
	}
}

void Menu::addFormattedSimpleItem(int option, string label) {
	stringstream menustream = stringstream();
	menustream << option << " - " << label;
	addSimpleItem(menustream.str());
}

void Menu::addFormattedToggledItem(int option, string labelIfTrue,
	string labelIfFalse, bool* flag) {
	stringstream menustream1 = stringstream();
	menustream1 << option << " - " << labelIfTrue;

	stringstream menustream2 = stringstream();
	menustream2 << option << " - " << labelIfFalse;

	addToggledItem(menustream1.str(), menustream2.str(), flag);
}

void printPrePad(int &numPads, char padChar, Alignment alignment, bool printBorder) {
	if (printBorder) {
		cout << "| ";
		numPads -= 2;
	}
	if (alignment == Alignment::RIGHT) {
		for (int i = 0; i < numPads; i++) cout << padChar;
		numPads = 0;
	}
	else if (alignment == Alignment::CENTER) {
		for (int i = 0; i < numPads / 2; i++) cout << padChar;
		numPads -= numPads / 2;
	}
}
void printPostPad(int &numPads, char padChar, Alignment alignment, bool printBorder) {
	if (printBorder)
		numPads -= 2;
	if (alignment == Alignment::LEFT) {
		for (int i = 0; i < numPads - 1; i++) cout << padChar;
		numPads = 0;
	}
	else if (alignment == Alignment::CENTER) {
		for (int i = 0; i < numPads - 1; i++) cout << padChar;
	}
	if (printBorder)
		cout << " |";
}
void printPaddedString(string str, int padSize, Alignment alignment, char padChar, bool printBorder) {
	int numSpaces = padSize - (int) str.length();

	printPrePad(numSpaces, padChar, alignment, printBorder);
	cout << str;
	printPostPad(numSpaces, padChar, alignment, printBorder);

	cout << "\n";
}