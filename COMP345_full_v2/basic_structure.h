#pragma once

#ifndef _BASIC_STRUCTURE_H_
#define _BASIC_STRUCTURE_H_

#include "config.h"
#include "placeable.h"

#include "inv2.h"

#define LOCKED (0)
#define CLOSED (1)
#define OPEN (2)

class Lockable : public Placeable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Placeable);
		ar & BOOST_SERIALIZATION_NVP(code);
		ar & BOOST_SERIALIZATION_NVP(locked);
	}

	int code;
	bool locked; //0 = locked/closed, 1 = unlocked/closed, >1 = unlocked/open
	static const std::string symbol;

protected:
	Lockable() : code(rand()), locked(false) {}
	Lockable(std::string name) : code(rand()), locked(false) {}

public:
	virtual ~Lockable() {}
	KeyItem* getKey() { return new KeyItem(this->keyName(), code); }
	//void setLock(bool isLocked) { locked = isLocked; }
	//bool isLocked() { return locked; }
	void setLocked(bool isLocked) { locked = isLocked; }
	bool unlock(KeyItem aKey);
	bool isLocked() { return locked; }
	virtual unordered_set<Item*> removeAll() { return unordered_set<Item*>(); }
	virtual std::string keyName() { return "key"; }
	virtual bool isWalkable(){ return false; }
	virtual const std::string getSymbol() { return "L"; }
	virtual void updateLvl(int aLevel) {}
	virtual bool reset(){ return true; }
	virtual std::string toString(){ return " "; }
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

class Door : public Lockable//, public Placeable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{

		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Lockable);
	}

	static const std::string symbolOpen;
	static const std::string symbolClosed;

public:
	Door() {}
	~Door() {}
	void updateLvl(int aLevel){}
	const std::string getSymbol() { return this->isLocked() ? symbolClosed : symbolOpen; }
	bool isWalkable() { return !this->isLocked(); }
	std::string keyName() { return "Door Key"; }
	bool reset(){ return true; }
	unordered_set<Item*> removeAll(){ return unordered_set<Item*>(); }
};

class Chest : public Lockable, public MySerializable, public Subject
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Lockable);
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
	Chest() {}
	~Chest() {}
	const std::string getSymbol() { return (content.getBackPack().empty()) ? symbolOpen : symbolClosed; }
	void updateLvl(int aLevel);
	bool reset(){ return true; }

	bool addItem(Item* anItem);
	void removeItem(Item* anItem);
	unordered_set<Item*> getAll();
	unordered_set<Item*> removeAll();
	std::string keyName() { return "Chest Key"; }
	bool isWalkable() { return false; }
	unordered_set<Item*> open(){ return (!isLocked()) ? this->content.getBackPack() : unordered_set<Item*>(); }

	void load(std::string filename);
	void save(std::string filename);

	std::string toString();
};

#endif _BASIC_STRUCTURE_H_