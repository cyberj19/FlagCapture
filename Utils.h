#pragma once
#include <conio.h>
#include <windows.h>
#include <string>
#include "Menu.h"
#include "Position.h"

int show_menu(Menu &menu, Position pos, int minChoice, int maxChoice);
void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor(); 

std::vector<std::string> split(std::string input, std::string delims);