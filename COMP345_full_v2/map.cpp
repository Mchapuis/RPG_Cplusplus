
#include "stdafx.h"
#include "map.h"

BOOST_CLASS_EXPORT_GUID(Map, "Map")

const Direction Direction::N = Direction(0, -1, 'w');
const Direction Direction::NE = Direction(1, -1, 'e');
const Direction Direction::E = Direction(1, 0, 'd');
const Direction Direction::SE = Direction(1, 1, 'c');
const Direction Direction::S = Direction(0, 1, 'x');
const Direction Direction::SW = Direction(-1, 1, 'z');
const Direction Direction::W = Direction(-1, 0, 'a');
const Direction Direction::NW = Direction(-1, -1, 'q');

std::map<char, const Direction*> Direction::keyMap = create_map();

//! @return a random direction (0 is North, 1 is N-East, etc.)
Direction Direction::randDir()
{
	switch (rand() % 7)
	{
	case 0: return N;
	case 1: return NE;
	case 2: return E;
	case 3: return SE;
	case 4: return S;
	case 5: return SW;
	case 6: return W;
	case 7: return NW;
	}
}

//! Default constructor for a Map.
/*! initializes a blank Map of size 10 x 10.*/
Map::Map() : height(5), width(5),
board(vector<vector<Cell*>>()),
stops(std::list<Cell*>())
{
	initMap();
	stops.push_front(board[0][0]);
	stops.push_back(board[this->getHeight()-1][this->getWidth()-1]);
	validPath();
}

Map::Map(std::string aName, int h, int w) :
name(aName), height(h), width(w),
board(vector<vector<Cell*>>()),
stops(std::list<Cell*>())
{
	initMap();
	stops.push_front(board[0][0]);
	stops.push_back(board[this->getHeight()-1][this->getWidth()-1]);
	validPath();
}

//! Map destructor.
Map::~Map()
{
	int i;
	int j;

	for (i = 0; i < this->getHeight(); i++)
	{
		for (j = 0; j < this->getWidth(); j++)
		delete board[i][j];
	}

}

//! Private function initializing the Map to the instantiated width and height.
void Map::initMap()
{
	board = vector<vector<Cell*>>(this->getHeight());
	int i;
	int j;
	int iOffset;
	int jOffset;
	int row;
	int col;

	for(i = 0; i < this->getHeight(); i++)
	{
		board[i] = vector<Cell*>(this->getWidth());

		for(j = 0; j < this->getWidth(); j++)
		{
			board[i][j] = new Cell(i, j);
		}//for j
	}//for i

	//Iterate through all cells
	for (i = 0; i < this->getHeight(); i++)
	{
		for (j = 0; j < this->getWidth(); j++)
		{
			//Iterate through all adjacent cells of each cell (3x3 square)
			for (iOffset = -1; iOffset <= 1; iOffset++)
			{
				for (jOffset = -1; jOffset <= 1; jOffset++)
				{
					//ignores itself
					if (iOffset == 0 && jOffset == 0)
					{
						continue;
					}

					row = i + iOffset;
					col = j + jOffset;

					//Add cell to adjacent list
					if (row >= 0 && row < this->getHeight() && col >= 0 && col < this->getWidth())
					{
						board[i][j]->addAdjacent(board[row][col]);
					}

				}//for jOffset
			}//for iOffset
		}//for j
	}//for i

}//initializeBoard()

void Map::reset()
{
	Placeable* temp;

	for (vector<Cell*> v : board)
	{
		for (Cell* c : v)
		{
			//Ckecks if cell is empty.
			//If not call reset on cell, initiates NPCs to lvl 0.
			//If returns false, remove content from cell.
			if (!c->isEmpty() && c->getContent()->reset() == false)
			{
				//removes player pointer from cell
				c->clear();
			}
		}
	}

}

bool Map::start(Player* aPlayer)
{
	this->reset();

	if (!this->validPath()) return false;
	
	stops.front()->setContent(aPlayer);
		
	for (vector<Cell*> v : board)
	{
		for (Cell* c : v)
		{
			if (!c->isEmpty())
			{
				c->getContent()->updateLvl(aPlayer->getLevel());
			}
		}
	}

	player = aPlayer;

	return true;
}

bool Map::cellExists(int row, int col)
{
	return (row >= 0 && row <= this->getHeight()-1 && col >= 0 && col <= this->getWidth()-1);
}

//! Function that returns a pointer to a board Cell.
Cell* Map::getCell(int row, int col)
{
	if (this->cellExists(row, col)) return board[row][col];

	return nullptr;
}

bool Map::isStop(Cell* aCell)
{
	for (Cell* c : stops)
	{
		if (aCell == c) return true;
	}

	return false;
}

bool Map::addStop(int row, int col, int position)
{
	int i;
	std::list<Cell*>::iterator it = stops.begin();

	if (this->cellExists(row, col) && !this->isStop(board[row][col]))
	{
		for (i = 1; i < position; i++)
		{
			it++;
		}

		stops.insert(it, board[row][col]); 
		return true;
	}

	return false;
}

bool Map::updateFirstStop(int row, int col)
{
	if (!stops.empty() && this->cellExists(row, col))
	{
		stops.pop_front();
		stops.push_front(board[row][col]);
		validPath();
		return true;
	}

	return false;
}

bool Map::updateLastStop(int row, int col)
{
	if (!stops.empty() && this->cellExists(row, col))
	{
		stops.pop_back();
		stops.push_back(board[row][col]);
		validPath();
		return true;
	}

	return false;
}



bool Map::removeStop(int row, int col, int position)
{
	int i;
	std::list<Cell*>::iterator it = stops.begin();
	
	if (this->cellExists(row, col))
	{
		for (i = 1; i < position; i++)
		{
			it++;
		}

		stops.erase(it);

		return true;
	}

	return false;
}

bool Map::addToCell(Placeable* toPlace, int row, int col)
{
	//cout << toPlace->getClassName() << " exists: " << this->cellExists(row, col) << endl;

	//cout << " empty: " << board[row][col]->isEmpty() << endl;
    //cout << board[row][col]->getContent()->getSymbol() << endl;

	if (this->cellExists(row, col) && board[row][col]->isEmpty())
	{
		board[row][col]->setContent(toPlace);
		return true;
	}

	return false;
}

//! Mehtod that instantiate Wall objects in a horizontal range Cell.
/*! @param row: the index of the row to set the Wall in.
@param start: the index of the cell at which to start the Wall.
@param end: the index of the Cell at which to end the Wall. */
bool Map::setRowWall(int row, int start, int end)
{
	int j;

	if (this->cellExists(row, start) && this->cellExists(row, end))
	{

		for (j = start; j < this->getWidth() && j <= end; j++)
		{
			board[row][j]->setContent(new Wall());
		}

		return true;
	}

	return false;
}

//! Mehtod that instantiate Wall objects in a vertical range Cell.
/*! @param col: the index of the col to set the Wall in.
@param start: the index of the cell at which to start the Wall.
@param end: the index of the Cell at which to end the Wall. */
bool Map::setColWall(int col, int start, int end)
{
	int i;

	if (this->cellExists(start, col) && this->cellExists(end, col))
	{

		for (i = start; i < this->getHeight() && i <= end; i++)
		{
			board[i][col]->setContent(new Wall());
		}

		return true;
	}

	return false;
}

Cell* Map::move(int srcRow, int srcCol, int destRow, int destCol)
{	
	Cell* src;
	Cell* dest;

	if (this->cellExists(srcRow, srcCol))
	{
		src = board[srcRow][srcCol];

		if (this->cellExists(destRow, destCol))
		{
			return move(src, board[destRow][destCol]);
		}

		return src;
	}
		
	return nullptr;
}

Cell* Map::move(int bRow, int bCol, Direction dir)
{
	if (this->cellExists(bRow, bCol))
	{
		return move(board[bRow][bCol], dir);
	}
	
	return nullptr;
}

//!@param: cell pointer of the source and a direction
//!Description: 
//!@return: a pointer to a cell
Cell* Map::move(Cell* source, Direction dir)
{
	// DESCRIPTION OF THIS LINE:  source->getRow() + dir.y_vel;
	// 1- get the row in the matrice...meaning the y and add the value
	// of the y direction value (0, 1 or -1)
	// 2- Then do the same thing with the column value and add the value
	int destRow = source->getRow() + dir.y_vel;
	int destCol = source->getCol() + dir.x_vel;

	//if cell is ok to move to
	if (this->cellExists(destRow, destCol))
	{
		//return where the cell is now
		return move(source, board[destRow][destCol]);
	}

	return source;
}

Cell* Map::move(Cell* source, Cell* dest)
{
	if (!source->isEmpty() && dest->isWalkable())
	{
		dest->setContent(source->getContent());
		source->clear();
		return dest;
	}

	return source;
}

bool Map::validPath()
{
	std::list<Cell*> myStops = stops;
	Cell* ref1 = myStops.front();
	Cell* ref2 = ref1;
	int col2;
	int row2;

	if (stops.size() < 2) return false;

	//get player's starting cell.


	do
	{
		ref1 = myStops.front();
		myStops.pop_front();
		
		ref2 = myStops.front();

		row2 = ref2->getRow();
		col2 = ref2->getCol();

		distanceGraph = dijkstra(ref1);

		if (distanceGraph[row2][col2] < 0) return false;
	} while (myStops.size() >= 2);	

	return true;
}

vector<vector<int>> Map::dijkstra(Cell* reference)
{
	return dijkstra(reference->getRow(), reference->getCol());
}

vector<vector<int>> Map::dijkstra(int const refRow, int const refCol)
{
	distanceGraph = initDistanceGraph();
	Cell* reference = board[refRow][refCol];
	Cell* currentCell;
	CellList borderList;
	CellSet borderSet;
	CellSet areaSet;
	int count = -1;

	borderSet.insert(reference);

	if (reference->isWalkable())
	{
		distanceGraph[refRow][refCol] = 0;
	}
	else
	{
		return distanceGraph;
	}

	do
	{
		borderList.addAll(borderSet.getSet());
		areaSet.addAll(borderSet.getSet());
		count++;

		while (borderList.empty() == false)
		{
			currentCell = borderList.remove();

			if (currentCell->isEmpty() || currentCell->isWalkable())
			{
				borderSet.addAll(currentCell->getAdjacent());
				distanceGraph[currentCell->getRow()][currentCell->getCol()] = count;
			}
		}

		borderSet.removeAll(areaSet.getSet());

		borderList.addAll(borderSet.getSet());

	} while (borderSet.empty() == false);

	return distanceGraph;
}


/*
int** Map::dijkstra(Cell* exit)
{
	int** distanceGraph = initDistanceGraph();
	int const exitRow = exit->getRow();
	int const exitCol = exit->getCol();
	Cell* currentCell;
	CellList borderList;
	CellSet borderSet;
	CellSet areaSet;
	int count = -1;

	borderSet.insert(exit);

	if (exit->isEmpty())
	{
		distanceGraph[exitRow][exitCol] = 0;
	}
	else
	{
		return distanceGraph;
	}

	do
	{
		borderList.addAll(borderSet.getSet());
		areaSet.addAll(borderSet.getSet());
		count++;

		while (borderList.empty() == false)
		{
			currentCell = borderList.remove();
			if (currentCell->isEmpty())
			{
				borderSet.addAll(currentCell->getAdjacent());
				distanceGraph[currentCell->getRow()][currentCell->getCol()] = count;
			}
		}

		borderSet.removeAll(areaSet.getSet());

		borderList.addAll(borderSet.getSet());

	} while (borderSet.empty() == false);

	return distanceGraph;
}
*/


//! Function that initialize a distance graph with all Cell distance set to -1
/*! The function is used by the djikstra function. All Cell it does not affect
@param pointer to an 2D integer array of the same height and width as Map
with all cells initialized to -1.*/
vector<vector<int>> Map::initDistanceGraph()
{
	vector<vector<int>> graph = vector<vector<int>>(this->getHeight());
	int i;
	int j;

	for (i = 0; i < this->getHeight(); i++)
	{
		graph[i] = vector<int>(this->getWidth());

		for (j = 0; j < this->getWidth(); j++)
		{
			graph[i][j] = -1;
		}
	}

	return graph;
}

std::string Map::toString2()
{
	std::string result = name + "\n\n";
	Cell* temp;
	int i;
	int j;
	auto line = [this]() 
	{
		int x;
		int y;
		std::string text = "   +";

		for (x = 0; x < this->getWidth(); x++)
		{
			for (y = 0; y < 3; y++)	text += "-";

			text += "+";
		}
		return text + '\n';
	};

	result += "    ";

	for (i = 0; i < this->getWidth(); i++)
	{
		result += " " + std::to_string(i);
		result += (i <= 9) ? "  " : " ";
	}

	result += '\n' + line();

	for (i = 0; i < this->getHeight(); i++)
	{
		result += std::to_string(i);
		result += (i <= 9) ? "  |" : " |";

		for (j = 0; j < this->getWidth(); j++)
		{
			result += " ";
			
			temp = board[i][j];

			if (!temp->isEmpty())
			{
				result += temp->toString();
			}
			else if (this->isStop(temp))
			{
				if (temp == stops.front())
				{
					result += "B";
				}
				else if (temp == stops.back())
				{
					result += "E";
				}
			}
			else
			{
				result += " ";
			}
			result += " |";
		}

		result += '\n' + line();
	}

	return result;
}


std::string Map::toString()
{
	std::string result = name + "\n\n";
	Cell* temp;
	int i;
	int j;

	for (i = 0; i < this->getWidth(); i++) result += "_";
	result += '\n';

	for (i = 0; i < this->getHeight(); i++)
	{
		for (j = 0; j < this->getWidth(); j++)
		{
			temp = board[i][j];

			if (!temp->isEmpty())
			{
				result += temp->toString();
			}
			else if (this->isStop(temp))
			{
				if (temp == stops.front())
				{
					result += "B";
				}
				else if (temp == stops.back())
				{
					result += "E";
				}
			}
			else
			{
				result += "_";
			}
		}

		result += '\n';
	}

	return result;
}

std::string Map::printGraph()
{
	stringstream stream;
	std::string result = name + " distance graph\n\n";
	Cell* temp;
	int i;
	int j;
	result += '\n';
	
	validPath();
	
	for (i = 0; i < this->getHeight(); i++)
	{
		for (j = 0; j < this->getWidth(); j++)
		{
			result += '[' + std::to_string(distanceGraph[i][j]) + ']';
		}

		result += '\n';
	}

	return result;
}

Map Map::sLoad(std::string filename)
{
	Map result = Map();
	(&result)->load(filename);
	return result;
}

void Map::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "maps\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Map::load(std::string filename)
{
	int i;
	int j;

	std::ifstream ifs(ASSETS_PATH + "maps\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{

		}
	}
}

//! Default constructor of a CellList object.
CellList::CellList()
{
	std::list<Cell*> cell_list;
}

//! Default CellList destructor
CellList::~CellList()
{
	cell_list.clear();
}

//! Accessor function to cell_list.
/*! return the list of Cell pointers cell_list.*/
std::list<Cell*> CellList::getList()
{
	return cell_list;
}

//! Function to add all of a set elements to cell_list.
/*! @param aSet: and Unordered_set of Cell pointers to add to the List cell_list.*/
void CellList::addAll(std::unordered_set<Cell*> aSet)
{
	for(Cell* c: aSet)
	{
		cell_list.push_front(c);
	}
}

//! Function that removes and returns the first element of the List cell_list.
/*! @return Cell pointer, first element of the Cell pointer list cell_list.*/
Cell* CellList::remove()
{
	Cell* c = cell_list.front();
	cell_list.pop_front();
	return c;
}

//! Asserts if cell_list is empty.
/*! return true if the Cell pointer List cell_list contains no elements.*/
bool CellList::empty()
{
	return cell_list.empty();
}

//! Default constructor of a CellSet object.
CellSet::CellSet()
{
	std::unordered_set<Cell*> cell_set;
}

//! Default CellSet destructor
CellSet::~CellSet()
{
	cell_set.clear();
}

//! Accessor function to cell_set.
/*! return the Unordered_set of Cell pointers cell_set.*/
std::unordered_set<Cell*> CellSet::getSet()
{
	return cell_set;
}

//! Function to that inserts a Cell pointer in cell_set.
/*! @param aCell: Cell pointer to insert in the Unordered_set cell_set.*/
void CellSet::insert(Cell* aCell)
{
	cell_set.insert(aCell);
}

//! Function to add all of a Cell pointer set elements to cell_set.
/*! @param aSet: an Unordered_set of Cell pointers to add to the Unordered_set cell_set.*/
void CellSet::addAll(std::unordered_set<Cell*> aSet)
{
	for (Cell* c: aSet)
	{
		cell_set.insert(c);
	}
}

//! Function to add all of a Cell pointer list elements to cell_set.
/*! @param aSet: a List of Cell pointers to add to the Unordered_set cell_set.*/
void CellSet::addAll(std::list<Cell*> aList)
{
	for (Cell* c: aList)
	{
		cell_set.insert(c);
	}
}

//! Function to remove all of a Cell pointer Unordered_set elements present in cell_set.
/*! @param aSet: an Unordered_set of Cell pointers to remove to the Unordered_set cell_set.*/
void CellSet::removeAll(std::unordered_set<Cell*> aSet)
{
	for (Cell* c : aSet)
	{
		cell_set.erase(c);
	}
}
//! Asserts if cell_set is empty.
/*! return true if the Cell pointer Unordered_set cell_set contains no elements.*/
bool CellSet::empty()
{
	return cell_set.empty();
}

//! Campain constructor, takes a string name.
Campain::Campain(string newName) : name(newName)
{ }

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