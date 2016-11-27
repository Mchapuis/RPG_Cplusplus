
#pragma once

#ifndef _CELL_H_
#define _CELL_H_

#include "config.h"
#include "placeable.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

class Cell
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(content);
		ar & BOOST_SERIALIZATION_NVP(row);
		ar & BOOST_SERIALIZATION_NVP(col);
	}

	Placeable* content;
	unordered_set<Cell*> adjacent;
	int row;
	int col;

	Cell::Cell() :
		row(-1), col(-1),
		content(nullptr),
		adjacent(std::unordered_set<Cell*>()) {}

public:
	static Cell* move(Cell* from, Cell* to);
	Cell::Cell(int newRow, int newCol) :
		row(newRow), col(newCol),
		content(nullptr),
		adjacent(std::unordered_set<Cell*>()) {}
	~Cell();
	const int getRow();
	const int getCol();
	std::unordered_set<Cell*> getAdjacent();
	void addAdjacent(Cell* aCell);
	void removeAdjacent(Cell* aCell);
	bool setContent(Placeable* newContent);
	Placeable* getContent() { return content; };
	void clear() { content = nullptr; }
	bool isWalkable();
	bool isEmpty();

	std::string toString();
};

#endif _CELL_H_



