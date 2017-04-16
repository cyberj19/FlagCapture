#pragma once
#include <conio.h>
#include <windows.h>


int show_menu(void (*printMenu)(void), int minChoice, int maxChoice);
void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor();