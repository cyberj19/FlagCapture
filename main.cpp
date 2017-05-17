#include "GameManager.h"
#include "BasicSettings.h"
#include <time.h>

using namespace std;

void main(int argc, char *argv[]) {
	// in the absence of exceptions mechanism
	// I have to implement this control flow
	// sorry for the long main

	srand((unsigned int)time(0));
	
	BasicSettings settings = BasicSettings(argc, argv);
	if (settings.hasErrors()) {
		cout << "There were errors: " << endl;
		settings.showErrors();
		cout << "Press any key to quit game...";
		_getch();
		return;
	}

	GameSettingsGenerator settingsGenerator = GameSettingsGenerator(settings);
	if (settingsGenerator.getNumSettings() == 0) {
		cout << "There are no available settings for game" << endl;
		cout << "Press any key to quit game...";
		_getch();
		return;
	}

	GameManager(settingsGenerator).run();
}
