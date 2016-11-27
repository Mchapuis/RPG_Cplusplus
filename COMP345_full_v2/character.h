
#pragma once

#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "config.h"
#include "inv2.h"
#include "placeable.h"
#include "basic_structure.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

//! Base class for character types Player, NpcEnepmy and Friendly.
/*! The GameCharacter object holds the the name, level, ability scores,
	bonus, modifiers, and Inventory of a character.
	It derives extends the abstract class Placeable.    
*/
class GameCharacter : public Placeable, MySerializable
{
private:
	// SERIALIZATION
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(MySerializable);
		ar & BOOST_SERIALIZATION_NVP(name);
		ar & BOOST_SERIALIZATION_NVP(level);
		ar & BOOST_SERIALIZATION_NVP(baseAtk);
		ar & BOOST_SERIALIZATION_NVP(Hp);
		ar & BOOST_SERIALIZATION_NVP(inventory);
		ar & BOOST_SERIALIZATION_NVP(abilities);
		//ar & BOOST_SERIALIZATION_NVP(modifiers);
	}
	
	//Saved
	std::string name;
	int level;
	int baseAtk;
	int Hp;
	int MaxHp;
	Inventory inventory;
	std::vector<int> abilities;
	//std::vector<int> modifiers;

	//Unsaved
	std::vector<int> bonus;

	static vector<int> abilitiesRoll();
	static int abilityRoll();
	void updateBonus();
	int hitDie();

	int damageRoll(int distance);
	int takeDamage(int damageValue);

	//! Inline function that calculates an ability bonus based on
	//! a given current ability score.
	int calcBonus(int baseStat) { return (baseStat / 2) - 5; }
	bool isWalkable() { return false; }

	static const std::string symbol;

protected:
	GameCharacter() {}

public:
	GameCharacter(std::string aName, int aBaseAtk, int aLevel);
	virtual ~GameCharacter() {}
	const std::string getSymbol() { return symbol; }
	std::string getName() { return name; }
	void setName(std::string aName){ name = aName; }
	virtual bool reset(){ return true; }
	void resetLevel(){ level = 0; }

	int getLevel() { return level; }
	void levelUp();
	virtual void updateLvl(int aLevel);

	bool unlock(Lockable* lock);

	Inventory getInventory() { return inventory; }

	int* getAllBaseAbl();
	int getBaseAbl(Ability abl);
	void setBaseAbl(Ability abl, int value);

	int* getAllBonus();
	int getBonus(Ability abl);

	int numOfAttacks() { return 1 + (level + baseAtk - 1)/5; }
	int AC() { return 10 + this->getNetStat(Ability::AC) + getBonus(Ability::DEX); }
	int ATK_Bonus(int NthAttack);

	void attack(GameCharacter opponent, int distance);

	//int* getAllEnchantments();
	//int getMod(Ability abl);
	//void setMod(Ability abl, int value);

	int* getAllNetStats();
	int getNetStat(Ability abl);

	bool addToPack(Item* anItem) { return inventory.addToPack(anItem); }
	void removeFromPack(Item* anItem){ inventory.removeFromPack(anItem); }
	bool equip(Equipment* anItem){ return inventory.equip(anItem); }
	bool unequip(EquipType aType){ return inventory.unequip(aType); }

	std::string toString();

	virtual void load(std::string filename){}
	virtual void save(std::string filename){}
};

class Player : public GameCharacter
{
private:
	// SERIALIZATION
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<GameCharacter>(*this);
	}

	static const std::string symbol;

public:
	static Player sLoad(std::string filename);
	Player() : GameCharacter("Unnamed", 1, 0) {}
	Player(std::string aName, int aBaseAtk, int aLevel) :
		GameCharacter(aName, aBaseAtk, aLevel) {}
	const std::string getSymbol() { return symbol; }
	bool isWalkable() { return true; }
	bool reset(){ return false; }

	void load(std::string filename);
	void save(std::string filename);
};

class NPC : public GameCharacter
{
private:
	// SERIALIZATION
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<GameCharacter>(*this);
	}

	static const std::string symbol;

protected:
	NPC() : GameCharacter("Unnamed", 1, 0) {}
public:
	NPC(std::string aName, int aBaseAtk, int aLevel) :
		GameCharacter(aName, aBaseAtk, aLevel) {}
	virtual ~NPC(){}
	const std::string getSymbol() { return symbol; }
	bool reset();

	virtual void getStrategy(){}

	virtual void load(std::string filename){}
	virtual void save(std::string filename){}
};

class Enemy : public NPC
{
private:
	// SERIALIZATION
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<NPC>(*this);
	}

	static const std::string symbol;

public:
	static Enemy sLoad(std::string filename);
	Enemy() : NPC("Unnamed", 1, 0) {}
	Enemy(std::string aName, int aBaseAtk, int aLevel) :
		NPC(aName, aBaseAtk, aLevel) {}
	const std::string getSymbol() { return symbol; }
	void getStrategy(){}
	bool isWalkable() {	return true;}

	void load(std::string filename);
	void save(std::string filename);
};

class Friendly : public NPC
{
private:
	// SERIALIZATION
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar & boost::serialization::base_object<NPC>(*this);
	}

	static const std::string symbol;

public:
	static Friendly sLoad(std::string filename);
	Friendly() : NPC("Unnamed", 1, 0) {}
	Friendly(std::string aName, int aBaseAtk, int aLevel) :
		NPC(aName, aBaseAtk, aLevel) {}
	const std::string getSymbol() { return symbol; }
	bool isWalkable() { return false; }
	void getStrategy(){}

	void load(std::string filename);
	void save(std::string filename);
};

#endif _CHARACTER_H_

