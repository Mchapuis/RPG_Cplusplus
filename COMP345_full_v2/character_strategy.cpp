#pragma once
#include "stdafx.h"
#include "character_strategy.h"
#include "map.h"

BOOST_CLASS_EXPORT_GUID(HumanPlayerStrategy, "HumanPlayerStrategy")
BOOST_CLASS_EXPORT_GUID(HostileStrategy, "HostileStrategy")
BOOST_CLASS_EXPORT_GUID(FriendlyStrategy, "FriendlyStrategy")

const int CharacterStrategy::SPEED = 5;
const int CharacterStrategy::LBS_LIMIT = 30;
const float CharacterStrategy::LBS_PENALTY = 0.33;
const int CharacterStrategy::SIGHT_DIST = 6;

//! @return: strait line distance between two cell
int CharacterStrategy::lineDist(Cell* c1, Cell* c2)
{
	float delta_x = std::abs(c2->getCol() - c1->getCol());
	float delta_y = std::abs(c2->getRow() - c1->getRow());

	return (int) std::ceil(std::sqrt(delta_x * delta_x + delta_y * delta_y));
}

//! @return: true if inside detection distance
bool CharacterStrategy::canSee(Cell* c1, Cell* c2)
{
	return lineDist(c1, c2) <= SIGHT_DIST;
}

//! @return: a matrice of numbers. -1 is wall. Other numbers represents # of steps to access the cell from the player's position
vector<vector<int>> CharacterStrategy::graph(Map* map, Cell* dest)
{
	return map->dijkstra(dest);
}

//! @return: cell (position)
Cell* CharacterStrategy::stepToward(vector<vector<int>> graph, Map* map, Cell* source, Cell* dest)
{
	int i;
	int j;

	for (i = 0; i < map->getHeight(); i++)
	{
		for (j = 0; j < map->getWidth(); j++)
		{
			if (graph[i][j] == 1) return (*map)[i][j];
		}
	}

	return nullptr;
}

//! @return: integer for speed of any game character
int CharacterStrategy::getSpeed(GameCharacter* me)
{
	return (me->getInventory()->getWeight() < LBS_LIMIT) ? SPEED : (int)(SPEED / LBS_PENALTY);
}

//!Will initiate the players menu action
//!---DESCRIPTION:
//!1- take the distance from graph to self --> return a matrice of numbers 
//!2- loop through all the cells in the map
//!3- give back the number of steps between each of elements in the map
//!4- if it is an ENNEMI, check if the range of the weapon reach him---yes? Give option to attack
//!5- if distance of 1 to a door or a chest, give option to open
void HumanPlayerStrategy::turn(std::map<Placeable*, Cell*> *objects)
{
	//step #1 
	distGraph = graph(map, (*objects)[me]);
	//step #2

	//iterator to go see each cell content
	for (std::pair<Placeable*, Cell*> p : *objects)
	{
		p.first;
		
	}


	for (int i = 0; i < objects->size(); i++){
		
	}

	int answer;

	cout << "what do you wish to do : ";

	cin >> answer;
}

//! @ return: number to adjust HP...not HP itself is returned
//! modifyHp sends the variation of HP, not the new HP
int HumanPlayerStrategy::takeDamage(GameCharacter* opponent, int damageValue)
{
	int damage = std::max(1, damageValue);

	return me->modifyHp(damage);
}


//!Hostile Ennemy stragtegy. Will seek the player if in a radius of 6 cells
//!and attack him as soon as he is in range, depending on his weapon.
void HostileStrategy::turn(std::map<Placeable*, Cell*> *objects)
{
	int i;

	int range = me->getRange(); //get weapon range

	int visibility = std::max(range, SIGHT_DIST);

	bool walking = true;

	std::map<Placeable*, Cell*>::iterator iter;
	Cell* temp = nullptr;
	Cell* myCell = (*objects)[me];
	Cell* playerCell = (*objects)[map->getPlayer()];

	distGraph = graph(map, playerCell);

	while (walking)
	{
		i = getSpeed(me);//speed is 3 now because there is no weight now.

		//cansee() give two cells - calculate linear distance, return true or false
		if (!canSee(myCell, playerCell))
		{
			while (i > 0 && walking)//if my speed is bigger than 0 and I am still walking
			{
				//record the cell I am on
				temp = myCell;

				//loop while temp == myCell...
				//--if the movement is possible, the cell value will be different
				//--if the movement is impossible, the cell value returned is the same.
				do
				{
					//get a random direction form randDir()
					myCell = map->move(myCell, Direction::randDir());
					(*objects)[me] = myCell;//me is a placebale index value and myCell is the value attached to the index 
					//if the player is in the attack zone, stop to attack
					if (canSee(myCell, playerCell))
					{
						walking = false;
						break;
					}
				} while (temp == myCell);//while the cell I am on didn;t change...

				i--;
			}
		}

		//am I the the player and I can still move and my cell is not null --- see through walls
		if (canSee(myCell, playerCell) && i > 0 && temp != NULL)
		{
			while (i > 0)
			{
				i--;
				//need to fix stepToward! not working, asks oliver
				myCell = map->move(myCell, stepToward(distGraph, map, myCell, playerCell));
				(*objects)[me] = myCell;//Update the value

				//lineDist() -- strait line distance between ennemi and player
				// range is the weapon
				// stop walking to attack player
				if (lineDist(myCell, playerCell) <= range)
				{
					walking = false;
					break;
				}
			}
		}
	}

	//strait line distance
	if (lineDist(myCell, playerCell) <= range)
	{
		me->attack(map->getPlayer(), lineDist(myCell, playerCell));
	}
}

//! same as takeDamage of others..return an integer to change HP, not the new HP itself
int HostileStrategy::takeDamage(GameCharacter* attacker, int damageValue)
{
	int damage = std::max(1, damageValue);

	return me->modifyHp(damage);
}

//! Passive friendly strategy. Simply follows the player.
//! See HostileStrategy for description of function --- nearly the same
void FriendlyStrategy::turn(std::map<Placeable*, Cell*> *objects)
{
	int i;

	//Set to accomodate for an active friendly NPC in battles,
	//but not implemented yet.
	int range = me->getRange();

	int visibility = std::max(range, SIGHT_DIST);

	bool walking = true;

	std::map<Placeable*, Cell*>::iterator iter;
	Cell* temp = nullptr;
	Cell* myCell = (*objects)[me];
	Cell* playerCell = (*objects)[map->getPlayer()];

	distGraph = graph(map, playerCell);

	while (walking)
	{
		i = getSpeed(me);

		if (!canSee(myCell, playerCell))
		{
			while (i > 0 && walking)
			{
				temp = myCell;

				do
				{
					myCell = map->move(myCell, Direction::randDir());
					(*objects)[me] = myCell;//update value
					if (canSee(myCell, playerCell))
					{
						walking = false;
						break;
					}
				} while (temp == myCell);

				i--;
			}
		}

		if (canSee(myCell, playerCell) && i > 0 && temp != NULL)
		{
			while (i > 0)
			{
				i--;
				myCell = map->move(myCell, stepToward(distGraph, map, myCell, playerCell));
				(*objects)[me] = myCell;//update value!
				if (lineDist(myCell, playerCell) <= range)
				{
					walking = false;
					break;
				}
			}
		}
	}
}

//Friends will become actively hostile if hit by the player.
int FriendlyStrategy::takeDamage(GameCharacter* attacker, int damageValue)
{
	int damage = std::max(1, damageValue);

	if (attacker == map->getPlayer())
	{
		me->setStrategy(new HostileStrategy(me));
		this->~FriendlyStrategy();
	}

	return me->modifyHp(damage);
}
