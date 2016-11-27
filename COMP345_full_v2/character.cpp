
#include "stdafx.h"
#include "character.h"

BOOST_CLASS_EXPORT_GUID(GameCharacter, "GameCharacter")
BOOST_CLASS_EXPORT_GUID(Player, "Player")
BOOST_CLASS_EXPORT_GUID(NPC, "NPC")
BOOST_CLASS_EXPORT_GUID(Enemy, "Enemy")
BOOST_CLASS_EXPORT_GUID(Friendly, "Friendly")

const std::string GameCharacter::symbol = "G";
const std::string Player::symbol = "P";
const std::string NPC::symbol = "N";
const std::string Enemy::symbol = "X";
const std::string Friendly::symbol = "F";

//! Character parametrized constructor.
//! Takes a name and an initial level.
//! The assigned level generates a character with according stats.
GameCharacter::GameCharacter(string aName, int aBaseAtk, int aLevel) :
name(aName), level(0), baseAtk(aBaseAtk), Hp(0), inventory(Inventory())
{
	int i;

	abilities = abilitiesRoll();
	updateBonus();
	//modifiers = std::vector<int>(Ability::getCount());

	if (aLevel < 0) aLevel == 0;

	this->updateLvl(aLevel);
}

//Assume ability rools of 4d6 drop lowest, and 1d10 Hit Die. 
vector<int> GameCharacter::abilitiesRoll()
{
	vector<Ability> abls = Ability::getMainAbls();
	vector<int> result = vector<int>(6);

	int i;

	for (const Ability a : abls)
	{
		result[a.index] = abilityRoll();
	}

	//order the elements in the array
	std::sort(result[0], result[6]);

	return result;
}

//! Using 4d6 drop lowest rule.
int GameCharacter::abilityRoll()
{
	vector<int> dices = vector<int>();
	int result = 0;
	int i;

	for (i = 0; i < 4; i++)
	{
		dices.push_back(Dice::roll(1, 6));
	}

	sort(dices.begin(), dices.end());

	for (i = 0; i < 3; i++)
	{
		result += dices.back();
		dices.pop_back();
	}

	return result;
}

void GameCharacter::updateBonus()
{
	vector<Ability> mainAbls = Ability::getMainAbls();
	vector<int> result = vector<int>(abilities.size());
	int i;

	for (Ability a: mainAbls)
	{
		result[a.index] = calcBonus(abilities[a.index]);
	}

	bonus = result;
}

//! Function for a single level increment.
/*! The function gives the character an ability 
    point every 4 levels, as per D&D rules (here randomly)*/
void GameCharacter::levelUp()
{
	int i;

	level++;

	//randomly increase an ability bonus each 4 levels.
	if (level % 4 == 0)
	{
		i = rand() % 6;
		bonus[Ability::getMainAbls()[i].index]++;
	}

	updateBonus();

	MaxHp += this->hitDie();
	Hp = MaxHp;
}

//! Function to set a characters level.
/*! The function calls on GameCharacter::levelUP to
    ensure the character stats move up accordingly*/
void GameCharacter::updateLvl(int toLevel)
{
	if (toLevel < 0) toLevel = 0;

	if (level == 0 && toLevel > 0) inventory.updateLvl(toLevel);
	
	while (level < toLevel)	this->levelUp();
}

int GameCharacter::hitDie()
{
	int die;

	if (level == 1)
	{
		die = 10;
	}

	die = Dice::roll(1, 10);

	return die + bonus[Ability::CON.index];
}

int GameCharacter::damageRoll(int distance)
{
	Weapon* weapon = (Weapon*) this->getInventory().getEquipType(EquipType::WEAPON);
	pair<int, int> dmg;
	int range;
	int str;
	int dext;
	int roll;

	if (!weapon)
	{
		return 0;
	}
	else
	{
		dmg = weapon->getDamage();
		range = weapon->getRange();
		str = this->getNetStat(Ability::STR);
		dext = this->getNetStat(Ability::DEX);
		
		if (range > 1 && str > 0) str = 0;
		if (range <= 1) dext = 0;

		roll = Dice::roll(dmg.first, dmg.second);
		roll += str + dext;

		if (range > 1 && distance > range) roll -= 2 * (distance - range);
	}
}

bool GameCharacter::unlock(Lockable* lock)
{
	std::unordered_set<KeyItem*> keyChain;

	if (!lock->isLocked()) return lock->open();

	for (KeyItem* k : keyChain)
	{
		if (lock->unlock(*k))
		{
			keyChain.erase(k);
			delete k;
			return lock->open();
		}
	}

	return false;
}

void GameCharacter::attack(GameCharacter opponent, int distance)
{
	int attackCount = this->numOfAttacks();
	int d20;
	int atk_bonus;
	int i;

	//Loop through character number of attacks.
	for (i = 1; i < attackCount; i++)
	{
		atk_bonus = this->ATK_Bonus(i);

		// Roll 1d20
		d20 = Dice::roll(1, 20);

		// If roll 1, miss.
		if (d20 == 1) continue;

		//If roll 20, hit, and possibly critical.
		if (d20 == 20)
		{
			//Attack roll to see if critical hit.
			if (Dice::roll(1, 20, ATK_Bonus(i)) >= opponent.AC())
			{
				opponent.takeDamage(this->damageRoll(distance) * 2);
			}

			//Normal hit if not.
			opponent.takeDamage(this->damageRoll(distance));
		}
		//Complete standard attack roll if between 2 and 18.
		else if (d20 + ATK_Bonus(i) >= opponent.AC())
		{
			opponent.takeDamage(this->damageRoll(distance));
		}
	}
}

int GameCharacter::takeDamage(int damageValue)
{
	if (Hp > 0) Hp -= std::min(1, damageValue);

	return Hp;
}

//! Function that returns an array of a character
//! base ability scores
int* GameCharacter::getAllBaseAbl()
{
	int* result = new int[6];
	int i;

	for (i = 0; i < 6; i++)
	{
		result[i] = abilities[i];
	}

	return result;
}

//! Function that returns a single base ability of a character.
int GameCharacter::getBaseAbl(Ability abl)
{
	return abilities[abl.index];
}

//! Function that sets a single requested base ability of a character.
void GameCharacter::setBaseAbl(Ability abl, int value)
{
	abilities[abl.index] = value;
}

//! Function that returns an array of a character
//! ability bonus.
int* GameCharacter::getAllBonus()
{
	int* result = new int[6];
	int i;

	for (i = 0; i < 6; i++)
	{
		result[i] = bonus[i];
	}

	return result;
}

//! Function that returns a single ability bonus of a character.
int GameCharacter::getBonus(Ability abl)
{
	return calcBonus(abilities[abl.index]);
}

int GameCharacter::ATK_Bonus(int NthAttack)
{
	if (NthAttack > 0 && NthAttack <= numOfAttacks())
	{ 
		return (level + baseAtk - 1) - (numOfAttacks() - NthAttack) * 5;
	}

	return 0;
}

/*
//! Function that returns an array of a character
//! ability modifiers
int* GameCharacter::getAllEnchantments()
{
	int* result = new int[Ability::getCount()];
	int i;

	for (i = 0; i < Ability::getCount(); i++)
	{
		result[i] = modifiers[i];
	}

	return result;
}

//! Function that returns a single ability modifier of a character.
int GameCharacter::getMod(Ability abl)
{
	return modifiers[abl.index];
}

//! Function that sets a single base modifier ability of a character.
void GameCharacter::setMod(Ability abl, int value)
{
	modifiers[abl.index] = value;
}
*/

//! Function that returns an array of a character
//! net ability scores, with bonus and modifiers included
int* GameCharacter::getAllNetStats()
{
	int* result = new int[6];
	int* enchantments = inventory.getAllEquipMods();
	int i;

	for (i = 0; i < 6; i++)
	{
		result[i] = abilities[i] + enchantments[i];
		//result[i] = abilities[i] + modifiers[i] + itemModifiers[i];
	}

	return result;
}

//! Function that returns a single net ability score
//! of a character, with bonus and modifiers included.
int GameCharacter::getNetStat(Ability abl)
{
	return abilities[abl.index]
		+ bonus[abl.index]
		//+ modifiers[abl.index]
		+ inventory.getEquipMod(abl);
}

std::string GameCharacter::toString()
{
	std::string result = this->getClassName() + "Character\n";
	std::string temp = "";
	int i;
	int j;

	result += "Name:      " + name + '\n';
	result += "Level:     " + to_string(level) + '\n';
	result += "HP:        " + to_string(Hp) + '/' + to_string(MaxHp);
	
	result += "\n\nAbilities and Modifiers:\n";

	for (i = 0; i < abilities.size(); i++)
	{
		temp = Ability::get(i).abbr;

		while (temp.size() < 7) temp += " ";

		temp += to_string(abilities[i]);

		if (bonus[i] != 0)
		{
			temp += " / " + to_string(bonus[i]);
		}

		result += temp + '\n';
	}

	return (result + inventory.toString());
}

bool NPC::reset()
{ 
	this->resetLevel();
	return true;
}

Player Player::sLoad(std::string filename)
{
	Player result = Player();
	(&result)->load(filename);
	return result;
}

void Player::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "characters\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Player::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "characters\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Enemy Enemy::sLoad(std::string filename)
{
	Enemy result = Enemy();
	(&result)->load(filename);
	return result;
}

void Enemy::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "characters\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Enemy::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "characters\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}

Friendly Friendly::sLoad(std::string filename)
{
	Friendly result = Friendly();
	(&result)->load(filename);
	return result;
}

void Friendly::save(std::string filename)
{
	std::ofstream ofs(ASSETS_PATH + "characters\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
}

void Friendly::load(std::string filename)
{
	std::ifstream ifs(ASSETS_PATH + "characters\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
}