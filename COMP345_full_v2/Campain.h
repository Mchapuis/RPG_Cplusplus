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

	string name;/**< Name of the campain */
	string description;/**< Description of the campain */
	list<Map*> maps;/**< List of maps of the campain */

public:
	Campain() {}
	~Campain() {}
	Campain(string newName, string newDesc);
	void setname(string newName);
	void setDesc(string desc);
	void addMapFront(Map* aMap);
	void addMapBack(Map* aMap);
	Map getNextMap();
	bool isEmpty();
};

#endif _CAMPAIN_H_