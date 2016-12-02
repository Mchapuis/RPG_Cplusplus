#include "stdafx.h"
#include "dice.h"

//! dice method. 
int Dice::roll(const int nbr_dice, const int faces)
{
	int result = 0;
	int i;
	Logger dicelogger("Dice Logger");
	std::string myString = "";
	
	for (i = 0; i < nbr_dice; i++)
	{
		result += rand() % faces + 1;
	}

	dicelogger.Update("Rolling " + to_string(nbr_dice) + "d" + to_string(faces) + ": " + to_string(result));
	return result;
}

int Dice::roll(const int nbr_dice, const int faces, const int modifier)
{
	return roll(nbr_dice, faces) + modifier;
}
