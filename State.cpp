#include "State.h"

void State::step()
{
	clock++;
	for (Soldier& soldier : soldiersA) {
		soldier.step();
	}
	
	for (Soldier& soldier : soldiersB) {
		soldier.step();
	}

}
