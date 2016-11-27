// COMP345_full_v0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "map.h"
#include "game.h"

#include <boost\serialization\export.hpp>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>

void testPlayer()
{
	std::ofstream ofs("test_file");

	Player p1 = Player("P1", 11, "F");
	Player p2 = Player("P2", 1, "F");

	cout << p1.getName() << " " << p1.getLevel() << endl;
	cout << p2.getName() << " " << p2.getLevel() << endl;

	{
		boost::archive::text_oarchive oa(ofs);

		oa << p1;
	}


	{
		std::ifstream ifs("test_file");
		boost::archive::text_iarchive ia(ifs);
		// read class state from archive
		ia >> p2;
		// archive and stream closed when destructors are called
	}

	cout << p2.getName() << " " << p2.getLevel() << endl;

}

void testMap()
{
	std::ofstream ofs("test_file");

	Map m1 = Map(10, 15);
	Map m2 = Map(21, 7);

	m1.setColWall(3, 0, 5);

	m1.print();
	m2.print();
	
	//cout << m1.WIDTH << " " << m1.HEIGHT;
	//cout << m2.WIDTH << " " << m2.HEIGHT;

	{
		boost::archive::text_oarchive oa(ofs);

		oa << m1;
	}


	{
		std::ifstream ifs("test_file");
		boost::archive::text_iarchive ia(ifs);
		// read class state from archive
		ia >> m2;
		// archive and stream closed when destructors are called
	}

	m2.print();
	//cout << m2.WIDTH << " " << m2.HEIGHT;

}

//Method to create items
void createItem()
{
	//type of item been created and for the constructor type
	int type;
	int addType;

	//item name
	string name;

	//weapong range type, malee or distance attack.
	int rangeType;
	
	//range for the distance attack weapon
	int addRange = 0;

	//variables for the enchantment array.
	int addATK;
	int addDMG;
	int addAC;
	int addSTR;
	int addCON;
	int addDEX;
	int addINTEL;
	int addWIS;
	int addCHA;

	//enchantment array
	vector<int> enchant = vector<int>(Ability::getCount());

	//inicializes array of enchantments to zero
	ItemBuilder builder = ItemBuilder();

	for (int i = 0; i < Ability::getCount(); i++)
	{
		enchant[i] = 0;
	}


	//MENU
	std::cout << "\n==============================\n";
	std::cout << "Welcome To The Item Creator!\n";
	std::cout << "\n==============================\n";
	do
	{
		std::cout << "\nPlease chose the item you want to create:\n";
		std::cout << "0 - Weapon\n";
		std::cout << "1 - ArmorType\n";
		std::cout << "2 - Helmet\n";
		std::cout << "3 - Belt\n";
		std::cout << "4 - Boots\n";
		std::cout << "5 - Shield\n";
		std::cout << "6 - Ring\n";
		std::cout << "7 - Exit\n";
		std::cin >> type;

		switch (type)
		{
			case 0: 
				std::cout << "\nCreating a Weapon:\n";
				std::cout << "Please give a name for your weapon:\n";
				std::cin >> name;
				do
				{
					std::cout << "0 - Short range weapon.\n";
					std::cout << "1 - Long range weapon\n";
					std::cin >> rangeType;
					if (rangeType == 0)
					{
						std::cout << "\nCreating a Short Range Weapon:\n";
						std::cout << "Range will be set to 1.\n";
						addRange = 1;
						do
						{
							std::cout << "\nDo you want to add Attack Bonus?\n";
							std::cout << "0 - No\n";
							std::cout << "1 - Yes.\n";
							std::cin >> addATK;
						} while (addATK > 1);
						do
						{
							std::cout << "\nDo you want to add Damage Bonus?\n";
							std::cout << "0 - No\n";
							std::cout << "1 - Yes.\n";
							std::cin >> addDMG;
						} while (addDMG > 1);
						enchant[0] = addATK;
						enchant[1] = addDMG;
						addType = 5;
					}
					else if (rangeType == 1)
					{
						std::cout << "\nCreating a Long Range Weapon:\n";
						//For final project the range will be from x to y.
						do
						{
							std::cout << "\nPlease choose the range (0-20):\n";
							std::cin >> addRange;
						} while (addRange > 20);
						do
						{
							std::cout << "\nDo you want to add Attack Bonus?\n";
							std::cout << "0 - No\n";
							std::cout << "1 - Yes.\n";
							std::cin >> addATK;
						} while (addATK > 1);
						do
						{
							std::cout << "\nDo you want to add Damage Bonus?\n";
							std::cout << "0 - No\n";
							std::cout << "1 - Yes.\n";
							std::cin >> addDMG;
						} while (addDMG > 1);
						enchant[0] = addATK;
						enchant[1] = addDMG;
						addType = 6;
					}
				} while (rangeType > 1);
				break;

		case 1:
			std::cout << "\nCreating a Body ArmorType:\n";
			std::cout << "\nPlease give a name for your Body ArmorType:\n";
			std::cin >> name;
			do
			{
				std::cout << "\nPlease choose a ArmorType Class:\n";
				std::cout << "0 - Light\n";
				std::cout << "1 - Medium.\n";
				std::cout << "2 - Heavy.\n";
				std::cin >> addAC;
			} while (addAC > 2);
			enchant[2] = addAC;
			addType = 2;
			break;

		case 2:
			std::cout << "\nCreating a Helmet:\n";
			std::cout << "\nPlease give a name for your Helmet:\n";
			std::cin >> name;
			do
			{
				std::cout << "\nPlease choose a ArmorType Class:\n";
				std::cout << "0 - Light\n";
				std::cout << "1 - Medium.\n";
				std::cout << "2 - Heavy.\n";
				std::cin >> addAC;
			} while (addAC > 2);
			do
			{
				std::cout << "\nDo you want to add Inteligence?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addINTEL;
			} while (addINTEL > 1);
			do
			{
				std::cout << "\nDo you want to add Wisdom?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addWIS;
			} while (addWIS > 1);
			enchant[2] = addAC;
			enchant[3] = addINTEL;
			enchant[4] = addWIS;
			addType = 1;
			break;

		case 3:
			std::cout << "\nCreating a Belt:\n";
			std::cout << "\nPlease give a name for your Belt:\n";
			std::cin >> name;
			do
			{
				std::cout << "\nDo you want to add Constitution?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addCON;
			} while (addCON > 1);
			do
			{
				std::cout << "\nDo you want to add Strenght?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addSTR;
			} while (addSTR > 1);
			enchant[4] = addCON;
			enchant[6] = addSTR;
			addType = 9;
			break;

		case 4:
			std::cout << "\nCreating a Boot:\n";
			std::cout << "\nPlease give a name for your Boot:\n";
			std::cin >> name;
			do
			{
				std::cout << "\nPlease choose a ArmorType Class:\n";
				std::cout << "0 - Light\n";
				std::cout << "1 - Medium.\n";
				std::cout << "2 - Heavy.\n";
				std::cin >> addAC;
			} while (addAC > 2);
			do
			{
				std::cout << "\nDo you want to add Dextery?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addDEX;
			} while (addDEX > 1);
			enchant[2] = addAC;
			enchant[5] = addDEX;
			addType = 3;
			break;

		case 5:
			std::cout << "\nCreating a Shield:\n";
			std::cout << "\nPlease give a name for your Shield:\n";
			std::cin >> name;
			do
			{
				std::cout << "\nPlease choose a ArmorType Class:\n";
				std::cout << "0 - Light\n";
				std::cout << "1 - Medium.\n";
				std::cout << "2 - Heavy.\n";
				std::cin >> addAC;
			} while (addAC > 2);
			enchant[2] = addAC;
			addType = 4;
			break;

		case 6:
			std::cout << "\nCreating a Ring:\n";
			std::cout << "\nPlease give a name for your Ring:\n";
			std::cin >> name;
			do
			{
				std::cout << "\nPlease choose a ArmorType Class:\n";
				std::cout << "0 - Light\n";
				std::cout << "1 - Medium.\n";
				std::cout << "2 - Heavy.\n";
				std::cin >> addAC;
			} while (addAC > 2);
			do
			{
				std::cout << "\nDo you want to add Strenght?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addSTR;
			} while (addSTR > 1);
			do
			{
				std::cout << "\nDo you want to add Constitution?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addCON;
			} while (addCON > 1);
			do
			{
				std::cout << "\nDo you want to add Wisdom?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addWIS;
			} while (addWIS > 1);
			do
			{
				std::cout << "\nDo you want to add Charisma?\n";
				std::cout << "0 - No\n";
				std::cout << "1 - Yes.\n";
				std::cin >> addCHA;
			} while (addCHA > 1);
			enchant[2] = addAC;
			enchant[4] = addCON;
			enchant[6] = addSTR;
			enchant[7] = addWIS;
			enchant[8] = addCHA;
			addType = 7;

			break;
		default:
			std::cout << "\nClosing program.\n";
			break;
	}

		if (type < 7)
		{
			builder.setType(addType);
			builder.setName(name);
			builder.setRange(addRange);
			builder.updateEnchantments(enchant);
			Item* someItem = builder.build();
			std::ofstream ofs(name);
			{
				boost::archive::text_oarchive oa(ofs);

				oa << someItem;
			}
			std::cout << "\n" << name << " was created.\n";

		}
		}while (type != 7);
}

void editItem()
{
	//enchantment array
	vector<int> enchant = vector<int>(Ability::getCount());

	//variables for the enchantment array.
	int addATK;
	int addDMG;
	int addAC;
	int addSTR;
	int addCON;
	int addDEX;
	int addINTEL;
	int addWIS;
	int addCHA;

	//variables to edit
	int addRange = 0;

	string itemName;
	Item* theItem = NULL;
	ItemBuilder builder = ItemBuilder();
	
	std::cout << "\n==============================\n";
	std::cout << "Welcome To The Item Editor!\n";
	std::cout << "\n==============================\n";
	do
	{
		std::cout << "What item do you want to edit?\n";
		std::cin >> itemName;
		theItem = Item::load(itemName);
	} while (theItem == NULL);

	int type = Equipment::DataMap::equipMap.at(theItem->getClassName());

	switch (type)
	{
	case 1:
		std::cout << "Editing Helmet:\n";
		do
		{
			std::cout << "\nPlease choose a ArmorType Class:\n";
			std::cout << "0 - Light\n";
			std::cout << "1 - Medium.\n";
			std::cout << "2 - Heavy.\n";
			std::cin >> addAC;
		} while (addAC > 2);
		do
		{
			std::cout << "\nDo you want to add Inteligence?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addINTEL;
		} while (addINTEL > 1);
		do
		{
			std::cout << "\nDo you want to add Wisdom?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addWIS;
		} while (addWIS > 1);
		enchant[2] = addAC;
		enchant[3] = addINTEL;
		enchant[4] = addWIS;
		break;
	case 2:
		std::cout << "Editing Body ArmorType:\n";
		do
		{
			std::cout << "\nPlease choose a ArmorType Class:\n";
			std::cout << "0 - Light\n";
			std::cout << "1 - Medium.\n";
			std::cout << "2 - Heavy.\n";
			std::cin >> addAC;
		} while (addAC > 2);
		enchant[2] = addAC;
		break;

	case 3:
		std::cout << "Editing Boot:\n";
		do
		{
			std::cout << "\nPlease choose a ArmorType Class:\n";
			std::cout << "0 - Light\n";
			std::cout << "1 - Medium.\n";
			std::cout << "2 - Heavy.\n";
			std::cin >> addAC;
		} while (addAC > 2);
		do
		{
			std::cout << "\nDo you want to add Dextery?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addDEX;
		} while (addDEX > 1);
		enchant[2] = addAC;
		enchant[5] = addDEX;
		break;

	case 4:
		std::cout << "Editing Shield:\n";
		do
		{
			std::cout << "\nPlease choose a ArmorType Class:\n";
			std::cout << "0 - Light\n";
			std::cout << "1 - Medium.\n";
			std::cout << "2 - Heavy.\n";
			std::cin >> addAC;
		} while (addAC > 2);
		enchant[2] = addAC;
		break;

	case 5:
		std::cout << "Editing Short Range Weapon:\n";
		std::cout << "Range will be set to 1.\n";
		addRange = 1;
		do
		{
			std::cout << "\nDo you want to add Attack Bonus?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addATK;
		} while (addATK > 1);
		do
		{
			std::cout << "\nDo you want to add Damage Bonus?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addDMG;
		} while (addDMG > 1);
		enchant[0] = addATK;
		enchant[1] = addDMG;
		break;
	case 6:
		std::cout << "Editing Long Range Weapon:\n";
		do
		{
			std::cout << "\nPlease choose the range (0-20):\n";
			std::cin >> addRange;
		} while (addRange > 20);
		do
		{
			std::cout << "\nDo you want to add Attack Bonus?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addATK;
		} while (addATK > 1);
		do
		{
			std::cout << "\nDo you want to add Damage Bonus?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addDMG;
		} while (addDMG > 1);
		enchant[0] = addATK;
		enchant[1] = addDMG;
		break;
	
	case 7:
		std::cout << "Editing Ring:\n";
		do
		{
			std::cout << "\nPlease choose a ArmorType Class:\n";
			std::cout << "0 - Light\n";
			std::cout << "1 - Medium.\n";
			std::cout << "2 - Heavy.\n";
			std::cin >> addAC;
		} while (addAC > 2);
		do
		{
			std::cout << "\nDo you want to add Strenght?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addSTR;
		} while (addSTR > 1);
		do
		{
			std::cout << "\nDo you want to add Constitution?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addCON;
		} while (addCON > 1);
		do
		{
			std::cout << "\nDo you want to add Wisdom?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addWIS;
		} while (addWIS > 1);
		do
		{
			std::cout << "\nDo you want to add Charisma?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addCHA;
		} while (addCHA > 1);
		enchant[2] = addAC;
		enchant[4] = addCON;
		enchant[6] = addSTR;
		enchant[7] = addWIS;
		enchant[8] = addCHA;
		break;

	case 8:
		break;
	case 9:
		std::cout << "Editing Belt:\n";
		do
		{
			std::cout << "\nDo you want to add Constitution?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addCON;
		} while (addCON > 1);
		do
		{
			std::cout << "\nDo you want to add Strenght?\n";
			std::cout << "0 - No\n";
			std::cout << "1 - Yes.\n";
			std::cin >> addSTR;
		} while (addSTR > 1);
		enchant[4] = addCON;
		enchant[6] = addSTR;
		break;

	default:
		break;
	}

	if (type < 7)
	{
		builder.updateEnchantments(enchant);
		builder.setRange(addRange);
		Item* someItem = builder.build();
		std::ofstream ofs(itemName);
		{
			boost::archive::text_oarchive oa(ofs);

			oa << someItem;
		}
	}
}

//method to set the enchantment of the items
void instantiateEnchant(string itemName, int playerLevel)
{
	vector<int> enchant = vector<int>(Ability::getCount());
	ItemBuilder builder = ItemBuilder();
	string name = itemName;
	Item* theItem = builder.build();

	theItem = Item::load(itemName);
	theItem->updateEnchantments(playerLevel);
}

//Method to call the insertChest from inventory
void insertChest(){
	int numChests;
	string itemName;
	Item* theItem = NULL;
	ItemBuilder builder = ItemBuilder();
	Chest aChest;
	std::cout << "How many items do you want to add to your Chest:";
	std::cin >> numChests;
	for (int x = 1; x <= numChests; x++)
	{
		do
		{
			std::cout << "Please insert " << x << " item name:";
			std::cin >> itemName;
			theItem = Item::load(itemName);
		}while (theItem == NULL);
		aChest.addItem(theItem);
	}
}


int mainMenu()
{
	/*
	int option;
	std::cout << "What do you want to do:\n";
	std::cout << "0 - Creat a Item\n";
	std::cout << "1 - Edit Item\n";
	std::cout << "2 - Set Enchantment Bonus\n";
	std::cout << "2 - Insert Items on Chest\n";
	std::cin >> option;
	if (option == 0)
	{
		createItem();
	}
	else if (option == 1)
	{
		editItem();
	}
	else if (option == 2)
	{
	instantiateEnchant("item2", 1);
	}
	else if (option == 3)
	{
	insertChest();
	}
	*/
	//editItem();
	
	//---------------------Martine Code to Play game------------------
	
	int i;
	std::string str_answer;
	std::string str_name;
	std::string str_map;

	//GAME LOOP
	//WELCOME SCREEN
	cout << "----------------------------------" << endl;
	cout << "------------WELCOME---------------" << endl;
	cout << "------------TO THE----------------" << endl;
	cout << "------TRUMP AMAZING RPG GAME------" << endl;
	cout << "----------------------------------" << endl;
	cout << "--By Aline, Olivier and Martine---" << endl;
	cout << "----------------------------------\n\n\n" << endl;
	Game game = Game();
	int page = 0;
	int subPage = 0;
	int subEditPage = 0;
	while (page != 9){
		if (page == 0){
		////////////////////////MAIN MENU////////////////////////
			cout << "Please Select an option:" << endl;
			cout << "NEW GAME--------enter 1" << endl;
			cout << "EDITOR----------enter 2" << endl;
			cout << "EXIT------------enter 9" << endl;
			cin >> page;
		}
		//IF the user wants to create a new game
		else if (page == 1){
			cout << "loading from default or from a saved file?" << endl;
			cout << "Enter D for default or S for saved" << endl;
			cin >> str_answer;
			if ((str_answer.compare("d") == 0|| str_answer.compare("D") == 0)){
				Map defaultMap;
				Player defaultPlayer;
				cout << "Creating default map and player..." << endl;
				cout << "***Reminder--> need to launch the game here...Line 149" << endl;
			}
			else if ((str_answer.compare("s") == 0 || (str_answer.compare("S") == 0))){
				
				//Asking for player name and loading it
				cout << "Loading..." << endl;
				Player currentPlayer = game.loadPlayer();
				
				//Asking for a map name and loading it
				cout << "***Reminder, please insert loadmap to play here...Line 158" << endl;
			}
			//loap Map
			cout << "launching the game...function to launch game here.." << endl;
			page = 9;//Should exit the function...
		}
		//if the user wants to edit something launch the SUBMENU
		else if (page == 2){
			//*******************************SUBMENU EDIT STARTS HERE***************************
			while (subPage != 3){
				if (subPage == 0){
					cout << "-------------------------------" << endl;
					cout << "------------EDIT MENU----------" << endl;
					cout << "-------------------------------" << endl;
					cout << "Please enter an option--->" << endl;
					cout << "Edit from save-----press 1" << endl;
					cout << "Create new---------press 2" << endl;
					cout << "Back---------------press 3" << endl;
					cin >> subPage;
				}
				//Edit
				if (subPage == 1){
					///////----------------------------------SUBMENU EDIT FROM LOAD STARTS HERE---------------------------------
					//launch the editing menu list
					while (subEditPage != 4){
						if (subEditPage == 0){
							cout << "-------------------------------" << endl;
							cout << "----What do you want to edit?--" << endl;
							cout << "-------------------------------" << endl;
							cout << "Please enter an option--->" << endl;
							cout << "MAP----------------press 1" << endl;
							cout << "CHARACTER----------press 2" << endl;
							cout << "ITEM---------------press 3" << endl;
							cout << "back---------------press 4" << endl;
							cin >> subEditPage;
						}
						//edit a map (default or saved...)
						else if (subEditPage == 1){
							Map map1;
							//map1 = game.loadMap();-------------------------------here this is creating an ERROR TNHKFDS
							game.mapEditor(map1);
							subEditPage = 0;//return to menu
						}
						//Edit a character from a load...
						else if (subEditPage ==2){
							game.createPlayerFromLoad();
							subEditPage = 0;//return to menu
						}
						//Edit an item from load...
						else if (subEditPage == 3){
							//Here are functions to edit items form load
							editItem();
							subEditPage = 0;//return to menu
						}
					}
					subPage = 0;//return to subMenu
				//-----------------------------------------------------SUBMENU EDIT FROM LOAD END HERE
				}
				//Create new!
				//-----------------------------------------------------SUBMENU CREATE START HERE
				else if (subPage == 2){
					while (subEditPage != 4){
						if (subEditPage == 0){
							cout << "-------------------------------" << endl;
							cout << "--What do you want to create?--" << endl;
							cout << "-------------------------------" << endl;
							cout << "Please enter an option--->" << endl;
							cout << "MAP----------------press 1" << endl;
							cout << "CHARACTER----------press 2" << endl;
							cout << "ITEM---------------press 3" << endl;
							cout << "back---------------press 4" << endl;
							cin >> subEditPage;
						}
						//CREATE A MAP
						else if (subEditPage == 1){
							Map mapDefault = Map();
							game.mapEditor(mapDefault);
							subEditPage = 0;
						}
						//CREATE A CHARACTER
						else if (subEditPage == 2){
							game.createPlayer();
							subEditPage = 0;
						}
						//CREATE AN ITEM
						else if (subEditPage == 3){
							createItem();
							subEditPage = 0;
						}
					}
					subPage = 0;
				//-------------------------------------------------SUBMENU CREATE ENDS HERE
				}
			}//END OF THE WHILE !=3 of SUBPAGE
			page = 0;
		}//END OF IF PAGE == 2
				
	}//END OF THE WHILE !=9...last while loop
	cin >> i;
	return 1;
	

}

int main(int argc, char *argv[])
{

}