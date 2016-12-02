#include "stdafx.h"
#include "basic_structure.h"

BOOST_CLASS_EXPORT_GUID(Lockable, "Lockable")
BOOST_CLASS_EXPORT_GUID(Wall, "Wall")
BOOST_CLASS_EXPORT_GUID(Door, "Door")
BOOST_CLASS_EXPORT_GUID(Chest, "Chest")

const std::string Lockable::symbol = "L";
const std::string Wall::symbol = "#";
const std::string Door::symbolOpen = "O";
const std::string Door::symbolClosed = "0";
const std::string Chest::symbolOpen = string(1, dollar);
const std::string Chest::symbolClosed = string(1, cent);


bool Lockable::unlock(KeyItem aKey)
{
	if (locked && code == aKey.getCode()) locked = false;

	return locked;
}

/*
bool Door::open(KeyItem* aKey)
{
	if (!this->isLocked())
	{
		opened = true;
		return true;
	}

	if (aKey != NULL) return this->unlock(*aKey);

	return false;
}

bool Chest::open(KeyItem* aKey)
{
	if (!this->isLocked())
	{
		opened = true;
		return true;
	}

	if (aKey != NULL) return this->unlock(*aKey);

	return false;
}
*/

bool Chest::addItem(Item* anItem)
{
	return content.addToPack(anItem);
}

void Chest::removeItem(Item* anItem)
{
	return content.removeFromPack(anItem);
}

unordered_set<Item*> Chest::getAll()
{
	return content.getBackPack();
}

unordered_set<Item*> Chest::removeAll()
{
	unordered_set<Item*> copyOfContent = unordered_set<Item*>();

	if (!this->isLocked())
	{
		copyOfContent = this->getAll();
		content = Inventory();
	}

	return copyOfContent;
}

void Chest::updateLvl(int aLevel)
{
	if (aLevel > 0) content.updateLvl(aLevel);
}

std::string Chest::toString()
{
	std::string result = "Chest:\n";
	return result + content.toString();
}

Chest Chest::sLoad(std::string filename)
{
	Chest result = Chest();
	(&result)->load(filename);
	return result;
}

void Chest::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Chest::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}
