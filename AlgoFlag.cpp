#include "GameManager.h"
#include "BasicSettings.h"
#include <time.h>

using namespace std;

void main(int argc, char *argv[]) {
	srand((unsigned int)time(0));
	try {
		BasicSettings settings = BasicSettings(argc, argv);
		GameSettingsGenerator settingsGenerator = 
			GameSettingsGenerator(settings);
		GameManager(settingsGenerator).run();
	}
	catch (std::string error) {
		cout << error << endl;
	}
	cout << "Press any key to quit game...";
	_getch();
}
