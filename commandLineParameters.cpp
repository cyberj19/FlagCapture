#include "commandLineParameters.h"

CommandLineParameters::CommandLineParameters(char *argv[], int argc)
{
	
	for (int i = 0; i < argc; ) {

		if (argv[i] == "-board") {
			board = (argv[i + 1] == "f") ? Board::F : Board::R;
			i += 2;
		}
		else if (argv[i] == "-moves") {
			moves = (argv[i + 1] == "f") ? Moves::F : Moves::K;
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

bool CommandLineParameters::getQuiet() const
{
	//quiet is active only if -board f -moves f
	if (board == Board::F && moves == Moves::F) {
		return quiet;
	}
	return false;
}

int CommandLineParameters::getDelay() const
{
	//if quiet is active (true) - delay is ignored
	return (quiet) ? 0 : delay; 
}