//! Base class of all items.
/* Contains a Builder to construct the items.
Protected constructor. */

#pragma once

#ifndef _INVENTORY2_H_
#define _INVENTORY2_H_

class Lockable;
class Item;

#include "config.h"

#include "serializable.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

#include "inventory_exceptions.h"

class Item : public MySerializable
{
private:
	// SERIALIZATION
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MySerializable);
		ar & BOOST_SERIALIZATION_NVP(name);
	}

	string name;

protected:
	Item(){}
	Item(std::string aName) : name(aName) {}

public:
	virtual ~Item() {}
	string getName()       { return name; }
	string getName() const { return name; }

	virtual std::string getClassName()       { return typeid(*this).name(); }
	virtual std::string getClassName() const { return typeid(*this).name(); }

	virtual void updateLvl(int playerLevel){}
	bool reset(){ return true; }

	virtual void save(std::string filename){}
	virtual void load(std::string filename){}

	virtual std::string toString(){ return name; }
};



class ItemComparator
{
public:
	bool operator()(const Item& item1, const Item& item2)
	{

		if (item1.getClassName() < item2.getClassName()) return true;
		if (item1.getClassName() == item2.getClassName()) return ( item1.getName() < item2.getName() );

		return false;
	}
};



class Equipment : public Item
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Item);
		ar & BOOST_SERIALIZATION_NVP(enchantments);
	}

	vector<int> enchantments;

	void initiate(EquipType const * aType);

protected:
	Equipment(){}
	Equipment(std::string aName, EquipType const * aType);
	virtual void setEnchantment(Ability abl, int bonus);
	

public:
	virtual ~Equipment() {}
	//vector<Ability> allowed();
	int* getAllEnchantments();
	int getEnchantment(Ability* abl);
	int getEnchantment(int index);
	//int getMod(Ability* abl)  { return enchantments[abl]; }
	//int getMod(int index)    { return enchantments[]; }
	void updateLvl(int playerLevel);

	virtual int getWeight(){ return 0; }

	virtual EquipType const * getType();

	std::string toString();

	virtual void save(std::string filename){}
	virtual void load(std::string filename){}
};



class ArmorPiece : public Equipment
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Equipment);
	}

	int weight;


protected:
	ArmorPiece() : weight(0) {}
	ArmorPiece(std::string aName, EquipType const * aType) :
		Equipment(aName, aType), weight(0) {}

public:
	virtual ~ArmorPiece(){}
	int getEnchantment(Ability abl);
	void setWeight(int newWeight){ weight = newWeight; }
	int getWeight(){ return weight; }
	virtual EquipType const * getType();

	virtual void save(std::string filename){}
	virtual void load(std::string filename){}
};



//! Helmet class.
//! Derives ArmorType.
class Helmet : public ArmorPiece
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ArmorPiece);
	}

public:
	static Helmet sLoad(std::string filename);
	Helmet(){}
	Helmet(std::string aName) : ArmorPiece(aName, this->getType()){}
	EquipType const * getType(){ return &EquipType::HELMET; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
	static Helmet* staticLoad(std::string filename);
};



//! Class for the main body protection EquipType.
//! Derives ArmorType.
class Cuirass : public ArmorPiece
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ArmorPiece);
	}

public:
	static Cuirass sLoad(std::string filename);
	Cuirass(){}
	Cuirass(std::string aName) : ArmorPiece(aName, this->getType()){}
	EquipType const * getType(){ return &EquipType::CUIRASS; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};


class Boots : public ArmorPiece
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ArmorPiece);
	}

public:
	static Boots sLoad(std::string filename);
	Boots(){}
	Boots(std::string aName) : ArmorPiece(aName, this->getType()){}
	EquipType const * getType(){ return &EquipType::BOOTS; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};



class Belt : public Equipment
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Equipment);
	}

public:
	static Belt sLoad(std::string filename);
	Belt(){}
	Belt(std::string aName) : Equipment(aName, this->getType()){}
	EquipType const * getType(){ return &EquipType::BELT; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};



class Ring : public Equipment
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Equipment);
	}

public:
	static Ring sLoad(std::string filename);
	Ring(){}
	Ring(std::string aName) : Equipment(aName, this->getType()){}
	EquipType const * getType(){ return &EquipType::RING; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};


class Shield : public Equipment
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Equipment);
	}

public:
	static Shield sLoad(std::string filename);
	Shield(){}
	Shield(std::string aName) : Equipment(aName, this->getType()){}
	EquipType const * getType(){ return &EquipType::SHIELD; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};


class Weapon : public Equipment
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Equipment);
		ar & BOOST_SERIALIZATION_NVP(range);
		ar & BOOST_SERIALIZATION_NVP(damage);

	}

	int range;
	std::pair<int, int> damage;

public:
	static Weapon sLoad(std::string filename);
	Weapon() : damage(pair<int, int>(1, 4)), range(1) {}
	Weapon(std::string aName, int aRange, int dmgNbrDice, int dmgDice);
	virtual EquipType const * getType(){ return &EquipType::WEAPON; }
	void setRange(int newRange) { if(range >= 1) range = newRange; }
	int getRange() { return range; }
	std::pair<int, int> getDamage() { return damage; }
	void setDamage(int dmgNbrDice, int dmgDice);

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};



//! Key item to unlock a Lockable item (chest, door)
//! Derives Item 
class KeyItem : public Item
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(Item);
		ar & BOOST_SERIALIZATION_NVP(code);
	}

	int code;

	KeyItem() {}

public:
	static KeyItem sLoad(std::string filename);
	KeyItem(std::string aName, int aCode) : Item(aName), code(aCode) {}
	int getCode() { return code; }

	virtual void save(std::string filename);
	virtual void load(std::string filename);
};

class Inventory
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_NVP(equipped);
		ar & BOOST_SERIALIZATION_NVP(backpack);
	}

	//Saved
	vector<Equipment*> equipped;
	unordered_set<Item*> backpack;
	
	/*
	//Unsaved
	Helmet** helmet;
	Cuirass** cuirass;
	Boots** boots;
	Ring** ring;
	Belt** belt;
	Shield** shield;
	Weapon** weapon;
	*/

public:
	Inventory();
	~Inventory();
	void updateLvl(int aLevel);
	Item* getEquipType(EquipType anEquip) { return equipped[anEquip.index]; }
	Equipment getEquipment(EquipType aType) { return *equipped[aType.index]; }
	int* getAllEquipMods();
	int getEquipMod(Ability abl);
	int getEquipMod(int index);
	int getWeight();
	unordered_set<Item*> getBackPack(){ return backpack; }
	bool addToPack(Item* anItem);
	void removeFromPack(Item* anItem) { backpack.erase(anItem); }
	bool equip(Equipment* anItem);
	bool unequip(EquipType aType);

	std::unordered_set<KeyItem*> keyChain();

	std::string toString();
};

#endif
