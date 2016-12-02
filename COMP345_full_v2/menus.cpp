#include "stdafx.h"
#include "menus.h"


//Menu to call different features.
void menuMenus()
{
	int answer = 0;
	while (answer != 9)
	{
		if (answer == 0){
			cout << "-------------------------------" << endl;
			cout << "--------------MENU-------------" << endl;
			cout << "-------------------------------" << endl;
			cout << "What do you want to do?" << endl;
			cout << "1 - Character Creator" << endl;
			cout << "2 - Campain Creator" << endl;
			cout << "3 - Map Creator" << endl;
			cout << "4 - Map Load and Edit" << endl;
			cout << "5 - Wrong Maps Tests" << endl;
			cout << "6 - Character Load and Edit" << endl;
			cout << "9 - Exit" << endl;
			cin >> answer;

			switch (answer)
			{
			case 1:
				characterCreator();
				break;
			case 2:
				campainCreator();
				break;
			case 3:
				mapCreator();
				break;
			case 4:
				mapEditor();
				break;
			case 5:
				wrongMaps();
				break;
			case 6:
				break;
			default:
				break;
			}
		}
	}
}

//CREATE A CHARACTER
//path to create a character is from editor ->create ->character
void characterCreator()
{
	string str_name;
	string str_answer;
	bool b_Continue = true;
	map<int, std::string> filesList;
	int itemNumber;
	vector<int> abilities; //to get abilities of the character
	Item* tempItem = nullptr;
	bool validEquip = true;
	const int ARRAY_SIZE = 6;
	//for random number for abilities
	int i_randomNumber;
	//for his level
	int i_level = 0;
	//maybe this array will not be used
	int abilityArray[ARRAY_SIZE];



	cout << "-------------------------------" << endl;
	cout << "-------CREATE A CHARACTER------" << endl;
	cout << "-------------------------------" << endl;

	///////////////NAME
	cout << "Please enter a name for you Character--->" << endl;
	cin >> str_name;

	//player to be created with abilities score
	cout << "Rolling the dice for each abilities...." << endl;
	Player pNew = Player(str_name, 1, 0);

	//vector of abilities
	abilities = pNew.getAllBaseAbl();
	cout << "Abilities:" << endl;
	cout << "------------------>STR: " << abilities[0] << endl;
	cout << "------------------>CON: " << abilities[1] << endl;
	cout << "------------------>DEX: " << abilities[2] << endl;
	cout << "------------------>INTL: " << abilities[3] << endl;
	cout << "------------------>WIS: " << abilities[4] << endl;
	cout << "------------------>CHA: " << abilities[5] << endl;


	/*
	//EQUIP ITEMS
	cout << "This is the list of saved items:" << endl;
	filesList = listFiles(ASSETS_PATH + "//items//");

	for (std::pair<int, std::string> p : filesList)
	{
		cout << p.first << ". " << p.second << endl;
	}
	do
	{
		for (EquipType e : EquipType::getTypes())
		{

			cout << "Please chose your " << e.name << endl;
			cin >> itemNumber;
			cout << filesList.count(itemNumber) << endl;
			if (filesList.count(itemNumber) > 0)
			{
				if (Equipment* e = dynamic_cast<Equipment*>(tempItem))
				{
					pNew.equip(e);
					cout << filesList[itemNumber] << " has been equipped." << endl;
				}
				else
				{
					cout << filesList[itemNumber] << " is not a valid equipment. " << endl;
				}

			}

			else if (itemNumber != 0)
			{
				cout << "Invalid option. ";
			}


		}

		for (Equipment* eq : pNew.getInventory()->getAllEquipment())
		{
			if (eq == NULL)
			{
				cout << "Missing: " << eq->getType()->name << "." << endl;
				validEquip = false;
			}
		}
	} while (validEquip == false);
	*/
	//
	//END
	cout << "Thank you for creating a character! Here are the statistcs" << endl;
	cout << "name: " << pNew.getName() << endl;
	cout << "level: " << pNew.getLevel() << endl;
	cout << "class " << pNew.getClassName() << endl;
	/////////////ABILITY MODIFIERS
	cout << "Abilities:" << endl;
	cout << "------------------>STR: " << abilities[0] << endl;
	cout << "------------------>CON: " << abilities[1] << endl;
	cout << "------------------>DEX: " << abilities[2] << endl;
	cout << "------------------>INTL: " << abilities[3] << endl;
	cout << "------------------>WIS: " << abilities[4] << endl;
	cout << "------------------>CHA: " << abilities[5] << endl;
	/*
	cout << "Equipment:" << endl;
	cout << "Belt:" << endl;
	cout << "Boots:" << endl;
	cout << "Cuirass:" << endl;
	cout << "Helmet:" << endl;
	cout << "Ring:" << endl;
	cout << "Shield:" << endl;
	cout << "Weapon:" << endl;
	*/
	cout << "Do you want to save this character? Please enter Y or N" << endl;
	cin >> str_answer;
	if ((str_answer.compare("Y") == 0) || (str_answer.compare("y") == 0)){

		//SAVING TO A FILE
		//name of file to load from
		cout << "Saving the character " << pNew.getName() << " -->    " << endl;

		pNew.save(pNew.getName());

		//pNew.load("filename");

		cout << "The Character has been saved!!! Thank you!" << endl;
	}
	else{
		cout << "Not saving the character!" << endl;
	}
	cout << "End of character creation..." << endl;

}

//!Method menu that calls campain to create one.
void campainCreator()
{
	Map* map1 = new Map("Map 1", 10, 10);
	Map* map2 = new Map("Map 2", 8, 8);
	Map* map3 = new Map("Map 3", 12, 12);

	int quantity;
	string name;
	string description;
	string mapName;
	cout << "WELCOME TO THE CAMPAIN CREATOR" << endl;
	cout << "How many maps do you want to put on the campain?" << endl;
	cin >> quantity;
	cout << "What will be the name of your campain?" << endl;
	cin >> name;
	cout << "Please insert a line of description for the campain?" << endl;
	cin >> description;
	Campain newCamp = Campain(name, description);
	cout << "Adding map 1, 2 and 3" << endl;
	newCamp.addMapBack(map1);
	newCamp.addMapBack(map2);
	newCamp.addMapBack(map3);

	Player *myPlayer = new Player();
	myPlayer->load("player1");

	while (newCamp.isEmpty() == true)
	{
		Map playMap = newCamp.getNextMap();
		cout << endl << playMap.toString2() << endl;
	}

}

//Method for the map creation
void mapCreator()
{
	string mapName;
	Map* aMap;
	int height;
	int width;
	int row;
	int column;
	string chestItem;
	int page = 0; //index for menu of map creation
	cout << "------------------------------------" << endl;
	cout << "---------USER MAP CREATION-----------" << endl;
	cout << "------------------------------------\n" << endl << endl;
	cout << "Please enter the map name: " << endl;
	cin >> mapName;
	cout << "Please enter the map height: " << endl;
	cin >> height;
	cout << "Please enter the map width:" << endl;
	cin >> width;
	aMap = new Map(mapName, height, width);
	cout << "Entry and Exit placed by default." << endl << endl;
	cout << "Here is the new map:" << endl;
	cout << endl << aMap->toString2() << endl;

	while (page != 9)
	{
		//show menu
		if (page == 0)
		{
			cout << "-------Mini Menu-----------" << endl;
			cout << "1 - insert chests" << endl;
			cout << "2 - insert NPC enemy" << endl;
			cout << "3 - insert NPC friend" << endl;
			cout << "4 - set Entry/Exit" << endl;
			cout << "5 - insert Walls" << endl;
			cout << "6 - remove Walls" << endl;
			cout << "7 - insert Door" << endl;
			cout << "9 - Exit" << endl;
			cin >> page;
		}
		//set chests in the map
		else if (page == 1)
		{
			Chest aChest;
			cout << "---------CHEST CREATION-----------" << endl;
			cout << "Please enter a Row and a Column to put the chest:" << endl;
			cout << "Row-->" << endl;
			cin >> row;
			cout << "Column-->" << endl;
			cin >> column;
			aMap->addToCell((Placeable*)&aChest, row, column);
			/////////HOW TO ADD ITEM TO CHEST?????
			cout << "What item do you want to add to chest?" << endl;
			cin >> chestItem;
			cout << endl << aMap->toString2() << endl;

			//return to mini menu!
			page = 0;
		}
		//set NPC ennemi
		else if (page == 2)
		{
			/////////////Need to choose the loading enemy
			Enemy aEnemy;
			cout << "---------ENEMY CREATION-----------" << endl;
			cout << "Please enter a Row and a Column to set the NPC enemy origin:" << endl;
			cout << "Row--->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			aMap->addToCell((Placeable*)&aEnemy, row, column);

			cout << "Here is the map updated!" << endl;
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}
		//set NPC friend
		else if (page == 3)
		{
			Friendly aFriend;
			/////////////Need to choose the loading friend
			cout << "---------FRIEND CREATION-----------" << endl;
			cout << "Please enter a Row and a Column to set the NPC friend origin:" << endl;
			cout << "Row--->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			aMap->addToCell((Placeable*)&aFriend, row, column);
			cout << "Here is the map updated!" << endl;
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}

		//set entry/exit
		else if (page == 4)
		{
			cout << "---------ENTRY/EXIT CREATION-----------" << endl;
			cout << "Please enter Entry door Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter Entry door Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;
			aMap->updateFirstStop(row, column);

			cout << "Please enter Exit door Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter Entry door Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;
			aMap->updateLastStop(row, column);
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}

		//set Walls
		else if (page == 5)
		{
			int end = 0;
			string str_answer;
			cout << "---------WALL CREATION-----------" << endl;
			cout << "Please enter the First cell of your wall with its row and column:" << endl;
			cout << "Row-->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			cout << "Do you want to build a vertical or horizontal wall?" << endl;
			cout << "Please enter V or H" << endl;
			cin >> str_answer;

			//if vertical
			if ((str_answer.compare("V") == 0) || (str_answer.compare("v") == 0))
			{
				cout << "Please enter the row you want your wall to end:--->" << endl;
				cin >> end;
				aMap->setRowWall(row, column, end);
				cout << "Here is the map updated" << endl;
				
			}
			//if horizontal
			else if ((str_answer.compare("H") == 0) || (str_answer.compare("h") == 0))
			{
				cout << "Please enter the column you want your wall to end:--->" << endl;
				cin >> end;
				aMap->setColWall(column, row, end);
				cout << "Here is the map updated" << endl;
			}
			cout << endl << aMap->toString2() << endl;
			//back to mini menu
			page = 0;
		}

		//remove object
		else if (page == 6)
		{
			cout << "---------OBJECT DESTRUCTION-----------" << endl;
			cout << "Please enter the object Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter the object Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;

			////////////HOW TO DELETE OBJECT??????
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}
		else if (page == 7)
		{
			cout << "---------DOOR CREATION-----------" << endl;

		}
		else{
			cout << "This is not a valid input for the menu!" << endl;
			//return to menu
			page = 0;
		}
	}//END OF WHILE LOOP FOR MINI MENU

	//SAVE OR DON'T SAVE THE MAP
	string save;
	cout << "Do you want to save the map? Y or N ---->" << endl;
	cin >> save;

	//IF YES
	if ((save.compare("Y") == 0) || (save.compare("y") == 0)){
		cout << "Before saving, we need to test the validity of the map..." << endl;
		if (aMap->validPath())
		{
			/////////////////save map
			cout << "Map saved.";
			page = 0;
		}
		else
		{
			cout << "Map invalid, no valid path to exit.";
		}
	}
	//IF NO --> USER DECIDED HE IS NOT SAVING
	else{
		cout << "We are not saving the map!" << endl;
		cout << "This is the end of the creation map ...." << endl;
	}
}

//Method to edit maps
void mapEditor()
{
	/*
	bool bValid = true;
	//name of file to load from
	string str_filename;
	//answer to save or not
	string save;

	//Default character so the file called isn't empty
	Map theMap = Map();

	//welcome screen
	cout << "----------------------------------" << endl;
	cout << "--------------LOADING A MAP---------" << endl;
	cout << "------------------------------------\n" << endl;
	cout << "Please enter the name of map file:" << endl;
	cin >> str_filename;

	//While the user didn't press Y to continue..
	//loop this:
	while (bValid == true)
	{
		cout << "Please enter the name of map file:" << endl;
		//getting input from user
		cin >> str_filename;
		cout << "Loading file...." << endl;

		/////////////HOW TO LOAD MAP

		cout << "Continue with this map? Enter Y or N -->" << endl;
		cin >> save;
		if (save.compare("Y") == 0 || save.compare("y") == 0)
		{
			cout << "Thank you!" << endl;
			cout << "Loading the game..." << endl;
			bValid = false;
		}
	}

	string mapName;
	Map* aMap;
	int height = 0;
	int width = 0;
	int row;
	int column;
	string chestItem;
	int page = 0; //index for menu of map creation
	cout << "------------------------------------" << endl;
	cout << "------------MAP EDITOR--------------" << endl;
	cout << "------------------------------------\n" << endl << endl;


	////put loaded map on a object////////<----------------
	aMap = new Map(mapName, height, width);
	cout << "Here is the loaded map:" << endl;
	cout << endl << aMap->toString2() << endl;

	while (page != 9)
	{
		//show menu
		if (page == 0)
		{
			cout << "-------Mini Menu-----------" << endl;
			cout << "1 - insert chests" << endl;
			cout << "2 - insert NPC enemy" << endl;
			cout << "3 - insert NPC friend" << endl;
			cout << "4 - set Entry/Exit" << endl;
			cout << "5 - insert Walls" << endl;
			cout << "6 - remove Walls" << endl;
			cout << "7 - insert Door" << endl;
			cout << "8 - change width and height" << endl;
			cout << "9 - Exit" << endl;
			cin >> page;
		}
		//set chests in the map
		else if (page == 1)
		{
			Chest aChest;
			cout << "---------CHEST CREATION-----------" << endl;
			cout << "Please enter a Row and a Column to put the chest:" << endl;
			cout << "Row-->" << endl;
			cin >> row;
			cout << "Column-->" << endl;
			cin >> column;
			aMap->addToCell((Placeable*)&aChest, row, column);
			/////////HOW TO ADD ITEM TO CHEST?????
			cout << "What item do you want to add to chest?" << endl;
			cin >> chestItem;
			cout << endl << aMap->toString2() << endl;

			//return to mini menu!
			page = 0;
		}
		//set NPC ennemi
		else if (page == 2)
		{
			/////////////Need to choose the loading enemy
			Enemy aEnemy;
			cout << "---------ENEMY CREATION-----------" << endl;
			cout << "Please enter a Row and a Column to set the NPC enemy origin:" << endl;
			cout << "Row--->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			aMap->addToCell((Placeable*)&aEnemy, row, column);

			cout << "Here is the map updated!" << endl;
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}
		//set NPC friend
		else if (page == 3)
		{
			Friendly aFriend;
			/////////////Need to choose the loading friend
			cout << "---------FRIEND CREATION-----------" << endl;
			cout << "Please enter a Row and a Column to set the NPC friend origin:" << endl;
			cout << "Row--->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			aMap->addToCell((Placeable*)&aFriend, row, column);
			cout << "Here is the map updated!" << endl;
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}

		//set entry/exit
		else if (page == 4)
		{
			cout << "---------ENTRY/EXIT CREATION-----------" << endl;
			cout << "Please enter Entry door Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter Entry door Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;
			aMap->updateFirstStop(row, column);

			cout << "Please enter Exit door Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter Entry door Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;
			aMap->updateLastStop(row, column);
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}

		//set Walls
		else if (page == 5)
		{
			int end = 0;
			string str_answer;
			cout << "---------WALL CREATION-----------" << endl;
			cout << "Please enter the First cell of your wall with its row and column:" << endl;
			cout << "Row-->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			cout << "Do you want to build a vertical or horizontal wall?" << endl;
			cout << "Please enter V or H" << endl;
			cin >> str_answer;

			//if vertical
			if ((str_answer.compare("V") == 0) || (str_answer.compare("v") == 0))
			{
				cout << "Please enter the row you want your wall to end:--->" << endl;
				cin >> end;
				aMap->setRowWall(row, column, end);
				cout << "Here is the map updated" << endl;

			}
			//if horizontal
			else if ((str_answer.compare("H") == 0) || (str_answer.compare("h") == 0))
			{
				cout << "Please enter the column you want your wall to end:--->" << endl;
				cin >> end;
				aMap->setColWall(column, row, end);
				cout << "Here is the map updated" << endl;
			}
			cout << endl << aMap->toString2() << endl;
			//back to mini menu
			page = 0;
		}

		//remove object
		else if (page == 6)
		{
			cout << "---------OBJECT DESTRUCTION-----------" << endl;
			cout << "Please enter the object Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter the object Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;

			////////////HOW TO DELETE OBJECT??????
			cout << endl << aMap->toString2() << endl;
			page = 0;
		}
		else if (page == 7)
		{
			cout << "---------DOOR CREATION-----------" << endl;

		}
		else{
			cout << "This is not a valid input for the menu!" << endl;
			//return to menu
			page = 0;
		}
	}//END OF WHILE LOOP FOR MINI MENU

	//SAVE OR DON'T SAVE THE MAP
	string save2;
	cout << "Do you want to save the map? Y or N ---->" << endl;
	cin >> save2;

	//IF YES
	if ((save2.compare("Y") == 0) || (save2.compare("y") == 0)){
		cout << "Before saving, we need to test the validity of the map..." << endl;
		if (aMap->validPath())
		{
			/////////////////save map
			cout << "Map saved.";
			page = 0;
		}
		else
		{
			cout << "Map invalid, no valid path to exit.";
		}
	}
	//IF NO --> USER DECIDED HE IS NOT SAVING
	else{
		cout << "We are not saving the map!" << endl;
		cout << "This is the end of the creation map ...." << endl;
	}
	*/
}

//method to test 3 wrong maps
void wrongMaps()
{
	cout << "Creating Wrong Map 1 - 10x10 with a wall blocking path." << endl;
	Map* wMap1 = new Map("Wrong Map 1", 10, 10);
	wMap1->setRowWall(5, 0, 9);
	cout << endl << wMap1->toString2() << endl;
	cout << "Before saving, we need to test the validity of the map..." << endl;
	if (wMap1->validPath())
	{
		/////////////////save map
		cout << "Map saved." << endl << endl;
	}
	else
	{
		cout << wMap1->getName() << " is invalid." << endl << endl;
	}
	system("pause");
	cout << "Creating Wrong Map 2 - 10x10 locked door on the way to chest with key." << endl;
	Map* wMap2 = new Map("Wrong Map 2", 10, 10);
	Chest wChest2;
	Door wDoor2;
	wMap2->setRowWall(5, 0, 4);
	wMap2->setRowWall(5, 6, 9);
	wMap2->addToCell((Placeable*)&wDoor2, 5, 5);
	wMap2->addToCell((Placeable*)&wChest2, 9, 0);
	wMap2->addStop(5, 5, 1);
	wChest2.addItem(wDoor2.getKey());
	cout << endl << wMap2->toString2() << endl;
	if (wMap2->validPath())
	{
		/////////////////save map
		cout << "Map saved." << endl << endl;
	}
	else
	{
		cout << wMap2->getName() << " is invalid." << endl << endl;
	}
	system("pause");
	cout << "Creating Wrong Map 3 - 10x10 with chest blocking exit." << endl;
	Map* wMap3 = new Map("wmap3", 10, 10);
	Chest wChest3;
	wChest3.load("chest1");
	wMap3->addToCell((Placeable*)&wChest3, 9, 9);
	cout << endl << wMap3->toString2() << endl;
	if (wMap3->validPath())
	{
		/////////////////save map
		cout << "Map saved." << endl << endl;
	}
	else
	{
		cout << wMap3->getName() << " is invalid." << endl << endl;
	}
}

//method to edit character
void characterEditor()
{
	bool bValid = true;
	//input to continue loop ..assigning x as a default
	std::string str_Value = "x";

	//name of file to load from
	std::string str_filename;

	//Default character so the file called isn't empty
	Player p0 = Player("Default Character", 1, 1);

	//Character that will hold the character information

	//Loading the file
	std::ofstream ofs("test_file");

	//printing to file
	{
		boost::archive::text_oarchive oa(ofs);
		oa << p0;
	}

	//welcome screen
	cout << "-------------------------------------" << endl;
	cout << "---------LOADING A CHARACTER---------" << endl;
	cout << "-------------------------------------" << endl;

	//While the user didn't press Y to continue..
	//loop this:
	while (bValid){
		cout << "Please enter a valid file name (test_file) -->    " << endl;

		//getting input from user
		cin >> str_filename;
		cout << "Loading file...." << endl;

		{
			std::ifstream ifs(str_filename);
			boost::archive::text_iarchive ia(ifs);
			// read class state from archive

			//Here we should add a foreach and loop throught all the characters in the files
			//Get the player that the user wants and load it

			ia >> p0;
			cout << "Name: " << p0.getName() << " level: " << p0.getLevel() << endl;
			// archive and stream closed when destructors are called
		}
		cout << "Continue with this character? Enter Y or N -->" << endl;
		cin >> str_Value;
		if (str_Value.compare("Y") == 0 || str_Value.compare("y") == 0){
			cout << "Thank you!" << endl;
			cout << "Loading the game..." << endl;
			bValid = false;
		}
	}
}