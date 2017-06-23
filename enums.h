#pragma once

enum class MenuOptions {
	NO_CHOICE = 0, SET_NAMES = 1, REGULAR_GAME = 2, SWITCHED_GAME = 3, RESET_SCORE = 4,
	TOGGLE_RECORDING = 5,
	EXIT_MENU = 9
};

enum class GameType {
	Attended,
	FileGame,
	AlgorithmGame
};

enum class SubMenuOptions { NO_CHOICE = 0, CONTINUE_GAME = 1, RESTART_GAME = 2, MAIN_MENU = 8, EXIT_GAME = 9 };

enum class MatchStage { START, INIT_DRAW, RUNNING, SUB_MENU, GAME_OVER };

enum class MatchOutput { WINNER_A, WINNER_B, TIE, MATCH_TERMINATED, QUIT_GAME };

enum class Player203398664 { A=1, B=2, NONE };

enum class Action { CHOOSE1, CHOOSE2, CHOOSE3, UP, DOWN, LEFT, RIGHT, NOACTION, ESC = 27 };

enum class SoldierType { S1, S2, S3 };

enum class SoldierStatus { ALIVE, DEAD };

enum class CellType { EMPTY, FOREST, SEA, FLAG_A, FLAG_B };

enum class BoardOptions { FromFile, Randomized };

enum class InputOptions { FromFile, Keyboard, Algorithm };

enum class errorMsg { WRONG_TOOL_PLAYER_A, WRONG_TOOL_PLAYER_B, WRONG_CHAR };