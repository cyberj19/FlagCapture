#pragma once
#include <conio.h>
#include <windows.h>
#include <string>

int show_menu(void (*printMenu)(void), int minChoice, int maxChoice);
int show_menu(std::string menu, int minChoice, int maxChoice);
void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor();