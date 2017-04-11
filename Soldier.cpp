#include "Soldier.h"

void Soldier::step()
{
	if (!isMoving || !isAlive()) return;
	if (state->getClock() % 2 == 1 && _player == Player::A) {
		stepLogic();
		// check direction on board
		//if forest or sea check type - if approved move else do nothing
		//if FlagA do nothing, if FlagB move -end game - you winner
		//if empty - check if there is an other soldier on this cell (is nullptr?)
		// if there is :if playerA -do nothing, if playerB -attack
		//if there isnt - move

	}
	else if (state->getClock() % 2 == 0 && _player == Player::B) {

	}
}

void Soldier::stepLogic()
{

}

// returns the winner of the battle
static Soldier & Soldier::battleWinner(Soldier & Attacker, Soldier & Defender)
{
	if (Attacker._player == Player::A)
	{
		if (Attacker._type == SoldierType::S1)
			return (isMatchLines(Defender.getX(), 10, 13) || isMatchLines(Defender.getY(), 4, 4)) ? Defender : Attacker;
		if (Attacker._type == SoldierType::S2) {
			if (Defender._type == SoldierType::S3)
				return Defender;
			else {
				return (isMatchLines(Defender.getX(), 3, 4) || isMatchLines(Defender.getY(), 11, 11)) ? Attacker : Defender;
			}
		}
		if (Attacker._type == SoldierType::S3) {
			return (isMatchLines(Defender.getX(), 8, 8) || isMatchLines(Defender.getY(), 7, 7)) ? Attacker : Defender;
		}	
	}
	else{
		Soldier& loser = battleWinner(Defender, Attacker); // there is a logical problem with this solution, because we rely on defender position as battleground,
		//and in this case we should reffer to "attacker's" position as battleground 
		//maybe we should add battleground parameter to the function to solve this.
		return (loser._player == Attacker._player) ? Defender : Attacker; 
	}
}

void Soldier::attack(Soldier & Attacker, Soldier & Defender)
{
	Soldier& winner = battleWinner(Attacker, Defender);
	if (winner._player == Attacker._player) {
		winner.move();
		Defender.die();
	}
	else {
		Attacker.die();
	}
}

bool isMatchLines(int myLine, int startLine, int stopLine) {
	for (int i = startLine; i <= stopLine; i++)
	{
		if (myLine == i)
			return true;
	}
	return false;
}
