#include "GameManager.h"
#include "BasicSettings.h"
#include <time.h>

using namespace std;

void main(int argc, char *argv[]) {
	srand(time(NULL));
	BasicSettings settings = BasicSettings(argc, argv);

	if (settings.hasErrors()) {
		cout << "There were errors: " << endl;
		settings.showErrors();
		cout << "Press any key to quit game...";
		getchar();
		return;
	}

	GameSettingsGenerator settingsGenerator = GameSettingsGenerator(settings);
	GameManager(settingsGenerator).run();
}
