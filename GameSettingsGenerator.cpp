#include "GameSettingsGenerator.h"

GameSettingsGenerator::GameSettingsGenerator(char *argv[], int argc)
{
	
	for (int i = 0; i < argc; ) {

		if (argv[i] == "-board") {
			boardOptions = (argv[i + 1] == "f") ? BoardInitOptions::FromFile : BoardInitOptions::Randomized;
			i += 2;
		}
		else if (argv[i] == "-moves") {
			movesOptions = (argv[i + 1] == "f") ? MovesSourceOptions::FromFile : MovesSourceOptions::Keyboard;
			i += 2;
		}
		else if (argv[i] == "-path") {
			path = argv[i + 1]; 
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
			delay = atoi(argv[i + 1]); //convert from char to int
			i += 2;
		}
		else {
			//the command line isn't valid

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
