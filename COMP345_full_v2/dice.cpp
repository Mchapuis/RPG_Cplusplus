#include "stdafx.h"
#include "dice.h"

//! dice method. 
int Dice::roll(const int nbr_dice, const int faces)
{
	int result = 0;
	int i;

	for (i = 0; i < nbr_dice; i++)
	{
		result += rand() % faces + 1;
	}

	return result;
}

int Dice::roll(const int nbr_dice, const int faces, const int modifier)
{
	return roll(nbr_dice, faces) + modifier;
}
