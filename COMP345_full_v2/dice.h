#pragma once

#ifndef _DICE_H_
#define _DICE_H_

#include "config.h"

class Dice
{
private:
	Dice();

public:
	static int roll(const int nbr_dice, const int faces);
	static int roll(const int nbr_dice, const int faces, const int modifier);
};

#endif