
#include "stdafx.h"
#include "inv2.h"

BOOST_CLASS_EXPORT_GUID(Item, "Item")
BOOST_CLASS_EXPORT_GUID(Equipment, "Equipment")
BOOST_CLASS_EXPORT_GUID(ArmorPiece, "ArmorPiece")
BOOST_CLASS_EXPORT_GUID(Helmet, "Helmet")
BOOST_CLASS_EXPORT_GUID(Cuirass, "Cuirass")
BOOST_CLASS_EXPORT_GUID(Boots, "Boots")
BOOST_CLASS_EXPORT_GUID(Ring, "Ring")
BOOST_CLASS_EXPORT_GUID(Belt, "Belt")
BOOST_CLASS_EXPORT_GUID(Shield, "Shield")
BOOST_CLASS_EXPORT_GUID(Weapon, "Weapon")
BOOST_CLASS_EXPORT_GUID(KeyItem, "KeyItem")

Equipment::Equipment(std::string aName, EquipType const * aType) : Item(aName)
{
	initiate(aType);
}


void Equipment::initiate(EquipType const * aType)
{	
	vector<Ability> allowed = aType->getEnchantments();
	int i;

	enchantments = vector<int>(Ability::getCount());
	
	for (i = 0; i < Ability::getCount(); i++)
	{
		enchantments[i] = 0;
	}
}


void Equipment::setEnchantment(Ability abl, int bonus)
{
	try
	{
		if (this->getType()->isAllowed(abl))
		{
			throw new IllegalEnchantmentException(this->getName(), this->getType()->name, abl.name);
		}
	}
	catch (IllegalEnchantmentException e)
	{
		cerr << e.what() << '\n';
	}

	enchantments[abl.index] = bonus;
}

//! Getter for the Abilities total
/*!
@return will returns the Abilities result
*/
int* Equipment::getAllEnchantments()
{
	int* result = new int[Ability::getCount()];
	int i;

	for (i = 0; i < Ability::getCount(); i++)
	{
		if (this->getType()->isAllowed(i))
		{
			result[i] = enchantments[i];
		}
		else
		{
			result[i] = 0;
		}
	}

	return result;
}

int Equipment::getEnchantment(Ability* abl)
{ 
	if (this->getType()->isAllowed(*abl))
	{
		return 0;
	}

	return enchantments[abl->index]; 
}

int Equipment::getEnchantment(int anIndex)
{
	Ability* abl = &Ability::get(anIndex);

	if (this->getType()->isAllowed(anIndex))
	{
		return 0;
	}

	return enchantments[anIndex];
}

EquipType const * Equipment::getType()
{
	try
	{
		throw new EmptyTypeException(this->getClassName());
	}
	catch (EmptyTypeException e)
	{
		cerr << e.what() << '\n';
		throw;
	}

	return &EquipType::HELMET;
}


EquipType const * ArmorPiece::getType()
{
	try
	{
		throw new EmptyTypeException(this->getClassName());
	}
	catch (EmptyTypeException e)
	{
		cerr << e.what() << '\n';
	}

	return &EquipType::HELMET;
}


//!Method to set the enchantment on the item acording to the player level on map load.
/*!
@param playerLevel: give the player level to set the Abilities (the ones that are on enchantments (1)) to it's level
*/
void Equipment::updateLvl(int playerLevel)
{
	vector<Ability> allowed = this->getType()->getEnchantments();
	int points = playerLevel;
	int bonus;
	float rnd;

	for (Ability a : allowed)
	{
		rnd = ( rand() % 100) / 100.0;
		bonus = min(points, min((int)(rnd * points), 5));
		//cout << "rnd:" << rnd << "  points:" << points << "  bonus:" << bonus << endl;
		enchantments[a.index] = bonus;
		points -= bonus;
	}
}

Weapon::Weapon(std::string aName, int aRange, int dmgNbrDice, int dmgDice)
: Equipment(aName, this->getType())
{
	damage = pair<int, int>(1, 4);

	range = (aRange <= 0)? 1: aRange;
	this->setDamage(dmgNbrDice, dmgDice);
}

void Weapon::setDamage(int dmgNbrDice, int dmgDice)
{
	if (dmgNbrDice > 1) damage.first = dmgNbrDice;
	if (dmgDice > 4) damage.second = dmgDice;
}

Inventory::Inventory() :
backpack(unordered_set<Item*>())
{
	int i;

	equipped = vector<Equipment*>(EquipType::getCount());

	for (i = 0; i < EquipType::getCount(); i++)
	{
		equipped[i] = nullptr;
	}
}

Inventory::~Inventory()
{
	for (Equipment* e : equipped)
	{
		delete e;
	}

	for (Item* i : backpack)
	{
		delete i;
	}
}

int* Inventory::getAllEquipMods()
{
	int* result = new int[Ability::getCount()];
	int i;
	int j;

	for (i = 0; i < Ability::getCount(); i++)
	{
		result[i] = 0;

		for (j = 0; j < EquipType::getCount(); j++)
		{
			if (equipped[j] != nullptr)
			{
				result[i] += equipped[j]->getEnchantment(i);
			}
		}
	}

	return result;
}

void Inventory::updateLvl(int aLevel)
{
	if (aLevel > 0) return;
	if (aLevel < 0) aLevel = 0;

	for (Equipment* e : equipped)
	{
		e->updateLvl(aLevel);
	}

	for (Item* it : backpack)
	{
		if (Equipment* eq = dynamic_cast<Equipment*>(it)) 
		{
			it->updateLvl(aLevel);
		}
	}
	
}

int Inventory::getEquipMod(Ability abl)
{
	int result = 0;
	int i;

	for (i = 0; i < EquipType::getCount(); i++)
	{
		if (equipped[i] != nullptr)
		{
			result += equipped[i]->getEnchantment(&abl);
		}
	}

	return result;
}

int Inventory::getEquipMod(int index)
{
	int result = 0;
	int i;

	for (i = 0; i < EquipType::getCount(); i++)
	{
		if (equipped[i] != nullptr)
		{
			result += equipped[i]->getEnchantment(index);
		}
	}

	return result;
}

int Inventory::getWeight()
{
	int result = 0;

	for (Equipment* e : equipped)
	{
		result += e->getWeight();
	}

	return result;
}

bool Inventory::addToPack(Item* anItem)
{
	if (backpack.count(anItem) > 0) return false;
	
	backpack.insert(anItem);
	return true;
}


bool Inventory::equip(Equipment* anItem)
{
	Equipment* temp;
	int i = anItem->getType()->index;

	if (equipped[i] == anItem) return false;

	if (equipped[i] != nullptr)
	{
		temp = equipped[i];
	}

	equipped[i] = anItem;
	this->removeFromPack(anItem);
	return true;
}

bool Inventory::unequip(EquipType aType)
{
	Equipment* temp;
	int i = aType.index;

	if (equipped[i] != nullptr)
	{
		temp = equipped[i];
		equipped[i] = nullptr;
		backpack.insert(temp);
		return true;
	}

	return false;
}

std::string Equipment::toString()
{
	std::string result = Item::toString()+"...";
	int i;

	while (result.size() < 20) result += " ";

	for (i = 0; i < Ability::getCount(); i++)
	{
		if (enchantments[i] > 0)
		{
			result += " " + Ability::get(i).abbr + ":" + std::to_string(enchantments[i]);
		}
	}

	return result;
}

std::unordered_set<KeyItem*> Inventory::keyChain()
{
	std::unordered_set<KeyItem*> result = std::unordered_set<KeyItem*>();
	
	for (Item* i : backpack)
	{
		if ((KeyItem*)i) result.insert((KeyItem*) i);
	}

	return result;
}

std::string Inventory::toString()
{
	std::string result = "";
	int i;
	
	result = "Equipped: \n";

	for (Equipment* e : equipped)
	{
		if (e != NULL || e != nullptr)	result += e->toString() + "\n";
	}

	result += "\nBackpack: \n";

	for (Item* e : backpack)
	{
		result += e->toString() + "\n";
	}

	return result;
}

Helmet Helmet::sLoad(std::string filename)
{
	Helmet result = Helmet();
	(&result)->load(filename);
	return result;
}

void Helmet::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Helmet::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Cuirass Cuirass::sLoad(std::string filename)
{
	Cuirass result = Cuirass();
	(&result)->load(filename);
	return result;
}

void Cuirass::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Cuirass::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Boots Boots::sLoad(std::string filename)
{
	Boots result = Boots();
	(&result)->load(filename);
	return result;
}

void Boots::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Boots::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Ring Ring::sLoad(std::string filename)
{
	Ring result = Ring();
	(&result)->load(filename);
	return result;
}

void Ring::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Ring::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Belt Belt::sLoad(std::string filename)
{
	Belt result = Belt();
	(&result)->load(filename);
	return result;
}

void Belt::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Belt::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Shield Shield::sLoad(std::string filename)
{
	Shield result = Shield();
	(&result)->load(filename);
	return result;
}

void Shield::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Shield::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Weapon Weapon::sLoad(std::string filename)
{
	Weapon result = Weapon();
	(&result)->load(filename);
	return result;
}

void Weapon::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Weapon::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

KeyItem KeyItem::sLoad(std::string filename)
{
	KeyItem result = KeyItem();
	(&result)->load(filename);
	return result;
}

void KeyItem::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void KeyItem::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}