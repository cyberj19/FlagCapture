#pragma once
#include<string>
#include<vector>
#include "MenuItem.h"
#include<Windows.h>

enum class Alignment { LEFT, CENTER, RIGHT };

class Menu {
	std::vector<MenuItem> menuItems;
	std::string _header;
	std::string _footer;
	bool _clearScreen;
public:
	Menu() : menuItems(), _header(""), _footer(""), _clearScreen(false) {}
	void setClearScreen(bool clearScreen) { _clearScreen = clearScreen; }
	void setHeader(std::string header) { _header = header; }
	void setFooter(std::string footer) { _footer = footer; }
	void addFormattedSimpleItem(int option, std::string label);
	void addSimpleItem(std::string label);
	void addFormattedToggledItem(int option, std::string labelIfTrue, std::string labelIfFalse, bool *flag);
	void addToggledItem(std::string labelIfTrue, std::string labelIfFalse, bool *flag);
	void printAtPosition(int x = 0, int y = 0);
private:
	void printHeader(int x, int y, int maxLine);
	void printItems(std::vector<std::string>& itemStrings, int x, int y, int maxLine);
	void printFooter(int x, int y, int maxLine);
	void printString(std::string str, int x, int y, int maxLine);
};

void printPrePad(int &numPads, char padChar, Alignment alignment, bool printBorder = false);
void printPostPad(int &numPads, char padChar, Alignment alignment, bool printBorder = false);
void printPaddedString(std::string str, int padSize, 
	Alignment alignment = Alignment::LEFT, char padChar = ' ', bool printBorder = false);
