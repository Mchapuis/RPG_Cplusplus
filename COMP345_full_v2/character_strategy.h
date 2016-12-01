#pragma once

#ifndef _CHARACTER_STRATEGY_H_
#define _CHARACTER_STRATEGY_H_

#include "config.h"
#include "placeable.h"
#include "dice.h"

class Map;
class Cell;
class GameCharacter;

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

#define AP (3) //action points

class CharacterStrategy 
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{}

public:
	static const int SPEED;
	static const int LBS_LIMIT;
	static const float LBS_PENALTY;
	static const int SIGHT_DIST;

	static int* actionPoints(){ return new int[3]{ 1, 1, 1 }; }
	static int getSpeed(GameCharacter* me);
	static int lineDist(Cell* c1, Cell* c2);
	static int walkDist(Cell* c1, Cell* c2);
	static bool canSee(Cell* c1, Cell* c2);
	static Cell* stepToward(Map* map, Cell* c1, Cell* c2);
	static vector<vector<int>> graph(Map* map, Cell* dest);

	virtual ~CharacterStrategy(){}
	virtual void turn(std::map<Placeable*, Cell*> *objects) = 0;
	virtual int takeDamage(GameCharacter* attacker, int damageValue) = 0;
	virtual void setMap(Map* aMap) = 0;
	//virtual string toString() = 0;//to print what is happening on screen
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(CharacterStrategy);



class HumanPlayerStrategy : public CharacterStrategy
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CharacterStrategy);
	}

	vector<vector<int>> distGraph;
	GameCharacter* me;
	Map* map;

	HumanPlayerStrategy(){}

public:
	HumanPlayerStrategy(GameCharacter* myself) : me(myself) {}
	void turn(std::map<Placeable*, Cell*> *objects); // unused by HumanToPcStrategy
	int takeDamage(GameCharacter* attacker, int damageValue);
	void setMap(Map* aMap){ map = aMap; }
	//string toString();
};



class HostileStrategy : public CharacterStrategy
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CharacterStrategy);
	}

	vector<vector<int>> distGraph;
	GameCharacter* me;
	Map* map;

	HostileStrategy(){}

public:
	HostileStrategy(GameCharacter* myself) : me(myself) {}
	void turn(std::map<Placeable*, Cell*> *objects);
	int takeDamage(GameCharacter* attacker, int damageValue);
	void setMap(Map* aMap){ map = aMap; }
	//string toString();
};



class FriendlyStrategy : public CharacterStrategy
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CharacterStrategy);
	}

	vector<vector<int>> distGraph;
	GameCharacter* me;
	Map* map;

	FriendlyStrategy(){}

public:

	FriendlyStrategy(GameCharacter* myself) : me(myself) {}
	void turn(std::map<Placeable*, Cell*> *objects);
	int takeDamage(GameCharacter* attacker, int damageValue);
	void setMap(Map* aMap){ map = aMap; }
	//string toString();
};


#endif