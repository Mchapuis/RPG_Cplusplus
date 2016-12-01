#include "stdafx.h"
#include "campain.h"



//! Campain constructor, takes a string name.
Campain::Campain(string newName)
{ 
	name = newName;
}

//! Campain destructor
void Campain::setDesc(string desc)
{
	description = desc;
}

//! Campain renaming function.
void Campain::rename(string newName)
{
	name = newName;
}

void Campain::addMapFront(Map* aMap)
{
	maps.push_front(aMap);
}

void Campain::addMapBack(Map* aMap)
{
	maps.push_back(aMap);
}

void Campain::addMapAt(Map* aMap, int position)
{
	list<Map*>::iterator it = maps.begin();

	advance(it, position);

	maps.insert(it, aMap);
}

void Campain::removeMap(Map* aMap)
{
	if (!maps.empty())
	{
		maps.remove(aMap);
	}
}

void Campain::removeMap(int position)
{
	list<Map*>::iterator it;

	if (!maps.empty())
	{
		it = maps.begin();

		advance(it, position);

		maps.erase(it);
	}
}

Map* Campain::operator[](int i)
{
	list<Map*>::iterator ite = maps.begin();

	return *ite;
}