#pragma once

#ifndef _CAMPAIN_H_
#define _CAMPAIN_H_

#include "config.h"
#include "map.h"

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

#endif _CAMPAIN_H_