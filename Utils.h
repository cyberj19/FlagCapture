#pragma once
#include <conio.h>
#include <windows.h>
#include <string>
#include "Menu.h"
#include "Pos203398664.h"
#include <vector>

int showMenu(Menu &menu, Pos203398664 pos, int minChoice, int maxChoice);
void setTextColor(int foreground_color, int background_color);
void setTextColor(int foreground_color);
void clearScreen();
void gotoxy(int x, int y);
void hideCursor(); 

std::vector<std::string> split(std::string input, std::string delims);
std::string stripExtension(const std::string& file);
void trim(std::string& str);
void trim(std::vector<std::string>& strings);
