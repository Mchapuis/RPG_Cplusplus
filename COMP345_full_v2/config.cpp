#include "stdafx.h"
#include "config.h"

int Ability::count = 0;

vector<Ability> Ability::indices = vector<Ability>();
vector<Ability> Ability::mainAbl = vector<Ability>();
const Ability Ability::STR = Ability("Strength", "Str", 1);
const Ability Ability::CON = Ability("Constitution", "Con", 1);
const Ability Ability::DEX = Ability("Dexterity", "Dex", 1);
const Ability Ability::INTL = Ability("Intelligence", "Int", 1);
const Ability Ability::WIS = Ability("Wisdom", "Wis", 1);
const Ability Ability::CHA = Ability("Charisma", "Cha", 1);
const Ability Ability::HP = Ability("Hit Points", "HP", 0);
const Ability Ability::ATK = Ability("Attack Bonus", "Atk", 0);
const Ability Ability::DMG = Ability("Damage Bonus", "Dmg", 0);
const Ability Ability::AC = Ability("Armor Class", "AC", 0);


int EquipType::count = 0;

const EquipType EquipType::HELMET = EquipType("Helmet", std::unordered_set<const Ability*>{  &Ability::AC, &Ability::INTL, &Ability::WIS, });
const EquipType EquipType::CUIRASS = EquipType("Armor", std::unordered_set<const Ability*>{ &Ability::AC });
const EquipType EquipType::BOOTS = EquipType("Boots", std::unordered_set<const Ability*>{ &Ability::AC, &Ability::DEX });
const EquipType EquipType::RING = EquipType("Ring", std::unordered_set<const Ability*>{ &Ability::AC, &Ability::STR, &Ability::CON, &Ability::WIS, &Ability::CHA });
const EquipType EquipType::BELT = EquipType("Belt", std::unordered_set<const Ability*>{ &Ability::STR, &Ability::CON });
const EquipType EquipType::SHIELD = EquipType("Shield", std::unordered_set<const Ability*>{ &Ability::AC });
const EquipType EquipType::WEAPON = EquipType("Weapon", std::unordered_set<const Ability*>{ &Ability::ATK, &Ability::DMG });

Ability::Ability(std::string aName, std::string anAbbr, int aPriority) :
index(count), name(aName), abbr(anAbbr), priority(aPriority)
{
	count++;
	indices.push_back(*this);
	if (aPriority == 1) mainAbl.push_back(*this);
}

vector<Ability> EquipType::getEnchantments() const
{
	vector<Ability> result = vector<Ability>();

	for (const Ability* a : stats)
	{
		result.push_back(*a);
	}

	return result;
}

const bool EquipType::isAllowed(const Ability abl) const
{
	if (stats.count(&abl) > 0)
	{
		return true;
	}

	return false;
}

const bool EquipType::isAllowed(int anIndex) const
{
	if (stats.count(&Ability::get(anIndex)) > 0)
	{
		return true;
	}

	return false;
}

//! dice method. 
int Dice::roll(const int nbr_dice, const int faces)
{
	int result = 0;
	int i;

	for (i = 0; i < nbr_dice; i++)
	{
		result += rand() % faces + 1;
	}

	return result;
}

int Dice::roll(const int nbr_dice, const int faces, const int modifier)
{
	return roll(nbr_dice, faces) + modifier;
}

//! Custom method to put a string to lowercase.
/*Method used to when sorting certain strings, such as item names
in a characters backpack.*/
string toLowerCase(string aString)
{
	int i;

	for (i = 0; i < (int)aString.size(); i++)
		aString[i] = (char)tolower(aString[i]);

	return aString;
}

map<int, std::string> listFiles(std::string folderName)
{
	map<int, std::string> result = map<int, std::string>();

	fs::path folder(folderName);
	fs::directory_iterator ite(folder);
	fs::directory_iterator ite_end;

	int i = 1;

	while (ite != ite_end)
	{
		try
		{
			if (fs::is_regular_file(ite->status()))
			{
				result.insert({ i++, ite->path().filename().string() });
			}
		}
		catch (const std::exception & ex)
		{
			std::cout << ite->path().filename() << " " << ex.what() << std::endl;
		}

		ite++;
	}

	return result;
}
