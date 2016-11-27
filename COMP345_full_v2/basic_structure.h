#pragma once

#ifndef _BASIC_STRUCTURE_H_
#define _BASIC_STRUCTURE_H_

#include "config.h"
#include "placeable.h"

#include "inv2.h"

#define LOCKED (0)
#define CLOSED (1)
#define OPEN (2)

class Lockable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(code);
		ar & BOOST_SERIALIZATION_NVP(status);
	}

	int code;
	bool status; //0 = locked/closed, 1 = unlocked/closed, >1 = unlocked/open

protected:
	Lockable() : code(rand()), status(1) {}
	Lockable(std::string name) : code(rand()), status(1) {}

public:
	virtual ~Lockable() {}
	KeyItem getKey() { return *(new KeyItem(this->keyName(), code)); }
	//void setLock(bool isLocked) { locked = isLocked; }
	//bool isLocked() { return locked; }
	int getStatus() { return status; }
	void setStatus(int aStatus) { status = (aStatus < 0) ? 0 : aStatus; }
	int unlock(KeyItem aKey);
	int open();
	bool isLocked() { return status == LOCKED; }
	bool isOpen() { return status == OPEN; }
	virtual std::string keyName() { return "key"; }
	void reset(){}
};

class Wall : public Placeable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Placeable);
	}

	static const std::string symbol;

public:
	~Wall() {}
	const std::string getSymbol() { return symbol; }
	void updateLvl(int aLevel){}
	bool isWalkable() { return false; }
	bool reset(){ return true; }
};

class Door : public Lockable, Placeable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{

		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Lockable);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Placeable);
	}

	static const std::string symbolOpen;
	static const std::string symbolClosed;

public:
	Door() {}
	~Door() {}
	void updateLvl(int aLevel){}
	const std::string getSymbol() { return this->isOpen() ? symbolOpen : symbolClosed; }
	bool isWalkable() { return !this->isLocked(); }
	std::string keyName() { return "Door Key"; }
	bool reset(){ return true; }
};

class Chest : public Lockable, Placeable, MySerializable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Lockable);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Placeable);
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MySerializable);
		ar & BOOST_SERIALIZATION_NVP(content);
	}

	Inventory content;

	static const char dollar = 36; //$
	static const std::string symbolOpen;

	static const char cent = 189; //¢
	static const std::string symbolClosed;

public:
	static Chest sLoad(std::string filename);
	Chest() { }
	~Chest() {} 
	const std::string getSymbol() { return this->isOpen() ? symbolOpen : symbolClosed; }
	void updateLvl(int aLevel);
	bool reset(){ return true; }

	bool addItem(Item* anItem);
	void removeItem(Item* anItem);
	unordered_set<Item*> getAll();
	unordered_set<Item*> removeAll();
	std::string keyName() { return "Chest Key"; }
	bool isWalkable() { return false; }

	void load(std::string filename);
	void save(std::string filename);

	std::string toString();
};

#endif _BASIC_STRUCTURE_H_