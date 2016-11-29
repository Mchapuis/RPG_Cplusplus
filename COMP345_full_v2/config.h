

#ifndef _CONFIG_H_
#define _CONFIG_H_

#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <typeinfo>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <array>
#include <vector>

#include <boost\serialization\string.hpp>
#include <boost\serialization\list.hpp>
#include <boost\serialization\vector.hpp>
#include <boost\serialization\utility.hpp>
#include <boost\serialization\set.hpp>
#include <boost\serialization\map.hpp>
#include <boost\serialization\unordered_map.hpp>
#include <boost\serialization\unordered_set.hpp>
#include <boost\serialization\base_object.hpp>

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/progress.hpp"

using namespace std;
namespace fs = boost::filesystem;


#define NBR_OF_ITEM_type (8)

const string ASSETS_PATH = ".\\assets\\";

map<int, std::string> listFiles(std::string folderName);

//! Ability index enumeration-like class
class Ability
{
public:
	static const Ability STR;
	static const Ability CON;
	static const Ability DEX;
	static const Ability INTL;
	static const Ability WIS;
	static const Ability CHA;
	static const Ability HP;
	static const Ability ATK;
	static const Ability DMG;
	static const Ability AC;

private:
	static vector<Ability> mainAbl;
	static vector<Ability> indices;
	static int count;
	int priority;
	Ability(std::string aName, std::string anAbbr, int aPriority);
	Ability(): index(0), name (""), abbr(""), priority(0) {}

public:
	const int index;
	const std::string name;
	const std::string abbr;
	static Ability get(int anIndex) { return indices[anIndex]; }
	static const int getCount() { return count; }
	static vector<Ability> getMainAbls() { return mainAbl; }
};

class EquipType
{
public:
	static const EquipType HELMET;
	static const EquipType CUIRASS;
	static const EquipType BOOTS;
	static const EquipType RING;
	static const EquipType BELT;
	static const EquipType SHIELD;
	static const EquipType WEAPON;

private:
	static int count;

	EquipType(std::string aName, std::unordered_set<const Ability*> enchantments) :
		index(count), name(aName), stats(enchantments) { count++; }

public:
	static const int getCount() { return count; }
	const std::unordered_set<const Ability*> stats;
	vector<Ability> getEnchantments() const;
	const int index;
	const std::string name;
	const bool isAllowed(const Ability abl) const;
	const bool isAllowed(int anIndex) const;
};

class Dice
{
private:
	Dice();

public:
	static int roll(const int nbr_dice, const int faces);
	static int roll(const int nbr_dice, const int faces, const int modifier);
};

class StringFunc
{
private:
	StringFunc();

public:
	static string toLowerCase(string aString);
};



#endif _CONFIG_H_