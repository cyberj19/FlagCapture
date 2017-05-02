#include "GameManager.h"
int main(int argc, char *argv[]) {
	GameSettingsGenerator settingsGenerator = GameSettingsGenerator(argc, argv);
	GameManager(settingsGenerator).run(); 
}
