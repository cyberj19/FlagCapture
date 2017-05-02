#include "GameManager.h"
int main(char *argv[], int argc) {
	GameSettingsGenerator settingsGenerator = GameSettingsGenerator(argv, argc);
	GameManager(settingsGenerator).run(); 
}
