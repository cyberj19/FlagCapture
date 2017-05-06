#include "GameManager.h"
#include <time.h>

void main(int argc, char *argv[]) {
	srand(time(NULL));
	GameSettingsGenerator settingsGenerator = GameSettingsGenerator(argc, argv);
	GameManager(settingsGenerator).run(); 
}
