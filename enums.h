#pragma once

enum MenuOptions { SET_NAMES = 1, REGULAR_GAME = 2, SWITCHED_GAME = 3, RESET_SCORE = 4, EXIT_MENU = 9 };
enum class Player { A, B };
enum class Action { CHOOSE1, CHOOSE2, CHOOSE3, UP, DOWN, LEFT, RIGHT, NOACTION };
enum class SoldierType { S1, S2, S3 };
enum SoldierStatus { ALIVE, DEAD };
enum class CellType { EMPTY, FOREST, SEA, FLAG_A, FLAG_B };