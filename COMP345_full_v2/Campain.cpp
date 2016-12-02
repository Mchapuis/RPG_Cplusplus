#include "stdafx.h"
#include "campain.h"


//!Campain constructor, takes a string name.
/*!
@param newName: name of the campain
@param newDesc: description of campain
*/
Campain::Campain(string newName, string newDesc)
{ 
	name = newName;
	description = newDesc;
}

//!Set description.
/*!
@param newDesc: new description of campain
*/
void Campain::setDesc(string newDesc)
{
	description = newDesc;
}

//!Set name.
/*!
@param newName: new name of campain
*/
void Campain::setname(string newName)
{
	name = newName;
}

//!Method to add map to the front of the list
/*!
@param aMap: map to be added.
*/
void Campain::addMapFront(Map* aMap)
{
	maps.push_front(aMap);
}

//!Method to add map to the back of the list
/*!
@param aMap: map to be added.
*/
void Campain::addMapBack(Map* aMap)
{
	maps.push_back(aMap);
}

Map* Campain::getNextMap()
{
	Map* aMap;
	aMap = maps.front();
	maps.pop_front();
	return aMap;
}

bool Campain::isEmpty()
{
	bool isEmpty = maps.empty();
	if (isEmpty == true)
	{
		return false;
	}
	else
	{
		return true;
	}
}
