
#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "config.h"

#include <utility>

#include "cell.h"
#include "character.h"
/*
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>
*/

using namespace std;

class Direction
{
public:

	static const Direction N;
	static const Direction NE;
	static const Direction E;
	static const Direction SE;
	static const Direction S;
	static const Direction SW;
	static const Direction W;
	static const Direction NW;

private:
	static std::map<char, const Direction*> keyMap;
	static std::map<char, const Direction*> create_map()
	{
		std::map<char, const Direction*> m = map<char, const Direction*>();
		m.insert({ N.key, &N });
		m.insert({ NE.key, &NE });
		m.insert({ E.key, &E });
		m.insert({ SE.key, &SE });
		m.insert({ S.key, &S });
		m.insert({ SW.key, &SW });
		m.insert({ W.key, &W });
		m.insert({ NW.key, &NW });
		return m;
	}

	Direction(const int xVel, const int yVel, const char aKey) :
		x_vel(xVel), y_vel(yVel), key(aKey) {}

public:
	static bool valid(char aChar) { return keyMap.count(aChar) > 0; }
	static map<char, const Direction*> getMap(){ return keyMap; }
	static Direction randDir();
	const int x_vel;
	const int y_vel;
	const char key;
};

//! Map object.
class Map: public MySerializable
{

private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MySerializable);
		ar & BOOST_SERIALIZATION_NVP(name);
		ar & BOOST_SERIALIZATION_NVP(board);
		ar & BOOST_SERIALIZATION_NVP(stops);
	}

	//saved
	std::string name;
	vector<vector<Cell*>> board;
	std::list<Cell*> stops;

	//unsaved
	int width;
	int height;

	Player* player;

	vector<vector<int>> distanceGraph;

	void initMap();
	vector<vector<int>> initDistanceGraph();
	bool isStop(Cell* aCell);

public:
	Map Map::sLoad(std::string filename);
	static const int** getDistanceGraph(int const exitRow, int const exitCol);
	Map();
	Map(std::string aName, int h, int w);
	~Map();
	void reset();
	bool start(Player* aPlayer);
	bool cellExists(int row, int col);

	vector<vector<Cell*>> getBoard() { return board; };
	int getWidth(){ return width; }
	int getHeight(){ return height; }

	void setName(std::string aName) { name = aName; }
	std::string getName() { return name; }

	Cell* getCell(int row, int col);
	void clearCell(int row, int col);

	bool addStop(int row, int col, int index);
	bool updateFirstStop(int row, int col);
	bool updateLastStop(int row, int col);
	bool removeStop(int row, int col, int position);
	Cell* getBegin() { return (!stops.empty())? stops.front(): nullptr;}
	Cell* getExit() { return (stops.size() >= 2) ? stops.back() : nullptr; }

	bool addToCell(Placeable* toPlace, int row, int col);
	bool setRowWall(int row, int from, int end);
	bool setColWall(int col, int from, int end);

	//3 first functions call the last one
	Cell* move(int srcRow, int srcCol, int destRow, int destCol);
	Cell* move(int bRow, int bCol, Direction dir);
	Cell* move(Cell* source, Direction dir);
	Cell* move(Cell* source, Cell* dest);

	Player* getPlayer(){ return player; }

	bool validPath();
	bool validPath(int beginRow, int beginCol, int exitRow, int exitCol);
	vector<vector<int>> dijkstra(int const refRow, int const refCol);
	vector<vector<int>> dijkstra(Cell* reference);

	bool operator==(Map& const rhsMap);
	bool operator!=(Map& const rhsMap);

	void load(std::string filename);
	void save(std::string filename);

	vector<Cell*> operator[](int i) { return board[i]; }

	std::string printGraph();
	std::string toString();
	std::string toString2();
};

class CellList
{
private:
	std::list<Cell*> cell_list;

public:
	CellList();
	~CellList();
	std::list<Cell*> getList();
	void addAll(std::unordered_set<Cell*> aSet);
	Cell* remove();
	bool empty();
};

class CellSet
{
private:
	std::unordered_set<Cell*> cell_set;

public:
	CellSet();
	~CellSet();
	std::unordered_set<Cell*> getSet();
	void insert(Cell* aCell);
	void addAll(std::unordered_set<Cell*> aSet);
	void addAll(std::list<Cell*> aList);
	void removeAll(std::unordered_set<Cell*> aSet);
	bool empty();
};

/*
class Campain
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(name);
		ar & BOOST_SERIALIZATION_NVP(description);
		ar & BOOST_SERIALIZATION_NVP(maps);
	}

	string name;
	string description;
	list<Map*> maps;
	Campain();

public:
	Campain(string newName);
	void rename(string newName);
	void setDesc(string desc);
	void addMapFront(Map* aMap);
	void addMapBack(Map* aMap);
	void addMapAt(Map* aMap, int position);
	void removeMap(Map* aMap);
	void removeMap(int position);

	Map* operator[](int i);
};
*/

#endif