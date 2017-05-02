#include "GameSettingsGenerator.h"

GameSettingsGenerator::GameSettingsGenerator(int argc, char *argv[])
	: boardOptions(BoardInitOptions::Randomized), 
	  movesOptions(MovesSourceOptions::Keyboard), 
	  path(), 
	  quiet(false), 
	  delay(20)
{
	
	for (int i = 1; i < argc; ) {
		if (strcmp(argv[i], "-board") == 0) {
			if (i == argc - 1) {
				//error;
			}
			else if (strcmp(argv[i + 1], "f") == 0) {
				boardOptions = BoardInitOptions::FromFile;
			}
			else if (strcmp(argv[i + 1], "r") == 0) {
				boardOptions = BoardInitOptions::Randomized;
			}
			else {
				//error;
			}
			i += 2;
		}
		else if (argv[i] == "-moves") {
			if (i == argc - 1) {
				//error;
			}
			else if (strcmp(argv[i + 1], "f") == 0) {
				movesOptions = MovesSourceOptions::FromFile;
			}
			else if (strcmp(argv[i + 1], "k") == 0) {
				movesOptions = MovesSourceOptions::Keyboard;
			}
			else {
				//error;
			}
			i += 2;
		}
		else if (argv[i] == "-path") {

			if (i == argc - 1) {
				//error;
			}
			else {
				path = std::string(argv[i + 1]);
			}
			i += 2;
		}
		else if (argv[i] == "-quiet") {
			//quiet is active only if -board f -moves f
			quiet = true;
			i += 1;
		}
		else if (argv[i] == "-delay") {
			//if quiet is active - delay is ignored
			//default is 20 ms
			if (i == argc - 1) {
				//error;
			}
			else {
				delay = atoi(argv[i + 1]);//convert from char to int
			}
			i += 2;
		}
		else {
			//the command line isn't valid
			//error
		}
	}
}

bool GameSettingsGenerator::getQuiet() const
{
	//quiet is active only if -board f -moves f
	if (boardOptions == BoardInitOptions::FromFile && movesOptions == MovesSourceOptions::FromFile) {
		return quiet;
	}
	return false;
}

int GameSettingsGenerator::getDelay() const
{
	//if quiet is active (true) - delay is ignored
	return (quiet) ? 0 : delay; 
}

bool GameSettingsGenerator::isAttended() const
{
	return movesOptions == MovesSourceOptions::Keyboard;
}

GameSettings GameSettingsGenerator::getNextSettings(bool recording)
{
	GameSettings settings = GameSettings(delay, quiet);

	if (boardOptions == BoardInitOptions::FromFile) {
		settings.setBoardInputFile("xxxx");
	}

	if (movesOptions == MovesSourceOptions::FromFile) {
		settings.setMovesInputFiles("XXX", "YYY");
	}

	if (recording) {
		settings.setRecordingOutputFiles("llll", "zzzz");
	}

	return settings;
}

bool GameSettingsGenerator::moreSettings()
{
	return false;
}
