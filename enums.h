#pragma once

enum class MenuOptions { 
	NO_CHOICE = 0, SET_NAMES = 1, REGULAR_GAME = 2, SWITCHED_GAME = 3, RESET_SCORE = 4, EXIT_MENU = 9 
};

enum class SubMenuOptions { NO_CHOICE = 0, CONTINUE_GAME = 1, RESTART_GAME = 2, MAIN_MENU = 8, EXIT_GAME = 9};

enum class MatchStage { START, INIT_DRAW, RUNNING, SUB_MENU, GAME_OVER };

enum class MatchOutput { WINNER_A, WINNER_B, MATCH_TERMINATED, QUIT_GAME };
enum class Player { A, B, NONE };

enum class Action { CHOOSE1, CHOOSE2, CHOOSE3, UP, DOWN, LEFT, RIGHT, NOACTION, ESC=27 };

enum class SoldierType { S1, S2, S3 };

enum class SoldierStatus { ALIVE, DEAD };

enum class CellType { EMPTY, FOREST, SEA, FLAG_A, FLAG_B };