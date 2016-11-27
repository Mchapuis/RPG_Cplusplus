
#include "stdafx.h"
#include "cell.h"

//! Board Cell destructor
Cell::~Cell()
{
	//delete content;
}

//! Accessor function for the cell column.
//! @return integer of the index of the cell column in its array.
const int Cell::getCol()
{
    return col;
}

//! Accessor function for the cell row.
//! @return integer of the index of the cell row in its array.
const int Cell::getRow()
{
    return row;
}

//! Accessor function for the cell adjacent cells.
//! @return unordered_set of cell pointers to each adjacent cells in the map.
std::unordered_set<Cell*> Cell::getAdjacent()
{
	return adjacent;
}

//! Function to add a cell pointer to the set of adjacent cells.
//! @param aCell: Cell pointer to add to the set of adjacent set.
void Cell::addAdjacent(Cell* aCell)
{
    adjacent.insert(aCell);
}

//! Function to remove a cell pointer to the set of adjacent cells.
//! @param aCell: Cell pointer to remove from the set of adjacent cells.
void Cell::removeAdjacent(Cell* aCell)
{
	adjacent.erase(aCell);
}

//! Function to push Placeable content on a Cell
bool Cell::setContent(Placeable* newContent)
{
	if (this->content == nullptr || this->isWalkable())
	{
		delete content;
		content = newContent;
		return true;
	}

	return false;
}

//! Function to check if the cell blocks a path or not. 
//! @return bool value, true if the cell's CellContent pointer is null
//! Or if it is walkable.
bool Cell::isWalkable()
{
	if (content == NULL) return true;
	
	return content->isWalkable();
}

//! Function to check if the cell holds some content or not. 
//! @return bool value, true if the cell's Placeable pointer is null.
bool Cell::isEmpty()
{
	return (content == NULL);
}

std::string Cell::toString()
{
	if (!this->isEmpty())
	{
		return content->getSymbol();
	}
	
	return "";
}