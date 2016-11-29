#include "stdafx.h"
#include "character_strategy.h"

BOOST_CLASS_EXPORT_GUID(HumanPlayerStrategy, "HumanPlayerStrategy")
BOOST_CLASS_EXPORT_GUID(HostileStrategy, "HostileStrategy")
BOOST_CLASS_EXPORT_GUID(FriendlyStrategy, "FriendlyStrategy")

const int CharacterStrategy::SPEED = 5;
const int CharacterStrategy::LBS_LIMIT = 30;
const float CharacterStrategy::LBS_PENALTY = 0.33;
const int CharacterStrategy::SIGHT_DIST = 6;

int CharacterStrategy::lineDist(Cell* c1, Cell* c2)
{
	float delta_x = std::abs(c2->getCol() - c1->getCol());
	float delta_y = std::abs(c2->getRow() - c1->getRow());

	return (int) std::ceil(std::sqrt(delta_x * delta_x + delta_y * delta_y));
}

bool CharacterStrategy::canSee(Cell* c1, Cell* c2)
{
	return lineDist(c1, c2) <= 6;
}

vector<vector<int>> CharacterStrategy::graph(Map* map, Cell* dest)
{
	return map->dijkstra(dest);
}

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

int CharacterStrategy::getSpeed(GameCharacter* me)
{
	return (me->getInventory()->getWeight() < LBS_LIMIT) ? SPEED : (int)(SPEED / LBS_PENALTY);
}

//!Will initiate the players menu action. Could not provide the menu at this time.
void HumanPlayerStrategy::turn(std::map<Placeable*, Cell*> objects)
{
	int answer;

	cout << "what do you wish to do : ";

	cin >> answer;
}

int HumanPlayerStrategy::takeDamage(GameCharacter* opponent, int damageValue)
{
	int damage = std::max(1, damageValue);

	return me->modifyHp(damage);
}

//!Hostile Ennemy stragtegy. Will seek the player if in a radius of 6 cells
//!and attack him as soon as he is in range, depending on his weapon.
void HostileStrategy::turn(std::map<Placeable*, Cell*> objects)
{
	int i;

	int range = me->getRange(); //get weapon range

	int visibility = std::max(range, SIGHT_DIST);

	bool walking = true;

	std::map<Placeable*, Cell*>::iterator iter;
	Cell* temp;
	Cell* myCell = objects[me];
	Cell* playerCell = objects[map->getPlayer()];

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

					if (canSee(myCell, playerCell))
					{
						walking = false;
						break;
					}
				} while (temp == myCell);

				i--;
			}
		}

		if (canSee(myCell, playerCell) && i > 0 && temp != 0)
		{
			while (i > 0)
			{
				i--;
				myCell = map->move(myCell, stepToward(distGraph, map, myCell, playerCell));
				
				if (lineDist(myCell, playerCell) <= range)
				{
					walking = false;
					break;
				}
			}
		}
	}

	if (lineDist(myCell, playerCell) <= range)
	{
		me->attack(map->getPlayer(), lineDist(myCell, playerCell));
	}
}

int HostileStrategy::takeDamage(GameCharacter* attacker, int damageValue)
{
	int damage = std::max(1, damageValue);

	return me->modifyHp(damage);
}

//! Passive friendly strategy. Simply follows the player.
void FriendlyStrategy::turn(std::map<Placeable*, Cell*> objects)
{
	int i;

	//Set to accomodate for an active friendly NPC in battles,
	//but not implemented yet.
	int range = me->getRange();

	int visibility = std::max(range, SIGHT_DIST);

	bool walking = true;

	std::map<Placeable*, Cell*>::iterator iter;
	Cell* temp;
	Cell* myCell = objects[me];
	Cell* playerCell = objects[map->getPlayer()];

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

					if (canSee(myCell, playerCell))
					{
						walking = false;
						break;
					}
				} while (temp == myCell);

				i--;
			}
		}

		if (canSee(myCell, playerCell) && i > 0 && temp != 0)
		{
			while (i > 0)
			{
				i--;
				myCell = map->move(myCell, stepToward(distGraph, map, myCell, playerCell));

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
