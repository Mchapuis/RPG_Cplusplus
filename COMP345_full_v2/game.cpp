#include "stdafx.h"
#include "game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::createPlayer()
{

}


/*
//CREATE A CHARACTER
//path to create a character is from editor ->create ->character
void Game::createPlayer(){
	std::string str_name;
	std::string str_gender;
	std::string str_answer;
	bool b_Continue = true;
	int *pointsTo; //to get abilities and modifiers and set them in the new character
	const int ARRAY_SIZE = 6;
	//for random number for abilities
	int i_randomNumber;
	//for his level
	int i_level = 0;
	//maybe this array will not be used
	int defaultArray[ARRAY_SIZE] = { 15, 14, 13, 12, 10, 8 };
	int abilityArray[ARRAY_SIZE];

	cout << "-------------------------------" << endl;
	cout << "-------CREATE A CHARACTER------" << endl;
	cout << "-------------------------------" << endl;

	///////////////NAME
	cout << "Please enter a name for you Character--->" << endl;
	cin >> str_name;

	//////////////GENDER
	cout << "Please enter a gender for you Character. Enter F or M or Other...---->" << endl;
	cin >> str_gender;

	//////////////LEVEL
	cout << "Please enter the level of your character: -------->" << endl;
	cin >> i_level;
	//player to be created
	Player pNew = Player(str_name, i_level, str_gender);
	/////////////ABILITY SCORES
	while (b_Continue){
		cout << "Ability Scores. Do you want default numbers or roll the 4d6 dice? " << endl;
		cout << "Default or Roll ? Enter D or R----->" << endl;
		cin >> str_answer;

		//'D' for default numbers
		//if the player wants the default, then assign the array with default numbers
		if ((str_answer.compare("D") == 0) || (str_answer.compare("d") == 0)){

			//set default numbers
			pNew.setBaseAbl(Ability::STR, defaultArray[0]);
			pNew.setBaseAbl(Ability::CON, defaultArray[1]);
			pNew.setBaseAbl(Ability::DEX, defaultArray[2]);
			pNew.setBaseAbl(Ability::INTL, defaultArray[3]);
			pNew.setBaseAbl(Ability::WIS, defaultArray[4]);
			pNew.setBaseAbl(Ability::CHA, defaultArray[5]);
		}
		//'R' for random numbers
		else if ((str_answer.compare("R") == 0) || (str_answer.compare("r") == 0)){
			for (int i = 0; i < ARRAY_SIZE; i++){
				abilityArray[i] = GameCharacter::abilityRoll();
			}
			//set random numbers
			pNew.setBaseAbl(Ability::STR, abilityArray[0]);
			pNew.setBaseAbl(Ability::CON, abilityArray[1]);
			pNew.setBaseAbl(Ability::DEX, abilityArray[2]);
			pNew.setBaseAbl(Ability::INTL, abilityArray[3]);
			pNew.setBaseAbl(Ability::WIS, abilityArray[4]);
			pNew.setBaseAbl(Ability::CHA, abilityArray[5]);
		}
		//pointer to array of abilities
		pointsTo = pNew.getAllBaseAbl();

		//-------Printing the array
		cout << "Rolling the dice for each abilities...." << endl;
		cout << "Your ability numbers are: [STR,CON,DEX,INTL,WIS,CHA]" << endl;
		cout << "------------------------> [";
		for (int i = 0; i < Ability::getCount(); i++){
			cout << " " << pointsTo[i] << ",";
		}
		cout << "]" << endl;
		//-------end of print array

		cout << "Do you want to rerun the dice? Enter Y or N" << endl;
		cin >> str_answer;
		if ((str_answer.compare("N") == 0) || (str_answer.compare("n") == 0)){
			b_Continue = false;
		}
	}
	/////////////END ABILITY SCORE
	pointsTo = pNew.getAllBonus();

	/////////////ABILITY MODIFIERS
	cout << "Based on your ability modifiers, here are your default bonus for each " << endl;
	cout << "------------------>[STR,CON,DEX,INTL,WIS,CHA]" << endl;
	cout << "------------------>[";
	for (int i = 0; i < Ability::getCount(); i++){
		abilityArray[i] = pointsTo[i];
		cout << "  " << pointsTo[i] << ",";
	}
	cout << "]" << endl;

	//set the ability modifiers (bonus) 
	pNew.setBonus(Ability::STR, abilityArray[0]);
	pNew.setBonus(Ability::CON, abilityArray[1]);
	pNew.setBonus(Ability::DEX, abilityArray[2]);
	pNew.setBonus(Ability::INTL, abilityArray[3]);
	pNew.setBonus(Ability::WIS, abilityArray[4]);
	pNew.setBonus(Ability::CHA, abilityArray[5]);

	//END
	cout << "Thank you for creating a character! Here are the statistcs" << endl;
	cout << "name: "<< pNew.getName() << endl;
	cout << "level: " << pNew.getLevel() << endl;
	cout << "class " << pNew.getClassName() << endl;
	pointsTo = pNew.getAllBaseAbl();
	cout << "Abilities: [STR,CON,DEX,INTL,WIS,CHA]" << endl;
	cout << "------------------------> [";
	for (int i = 0; i < Ability::getCount(); i++){
		cout << " " << pointsTo[i] << ",";
	}
	cout << "]" << endl;
	pointsTo = pNew.getAllBonus();
	cout << "Bonus------------->[STR,CON,DEX,INTL,WIS,CHA]" << endl;
	cout << "------------------>[";
	for (int i = 0; i < Ability::getCount(); i++){
		abilityArray[i] = pointsTo[i];
		cout << "  " << pointsTo[i] << ",";
	}
	cout << "]" << endl;

	cout << "Do you want to save this character? Please enter Y or N" << endl;
	cin >> str_answer;
	if ((str_answer.compare("Y") == 0) || (str_answer.compare("y") == 0)){

		//SAVING TO A FILE
		//name of file to load from
		cout << "Saving the character "<<pNew.getName()<<" -->    " << endl;

		//Loading the file
		std::ofstream ofs(pNew.getName());

		//printing to file
		{
			boost::archive::text_oarchive oa(ofs);
			oa << pNew;
		}
		cout << "The Character has been saved!!! Thank you!" << endl;
	}
	else{
		cout << "Not saving the character!" << endl;
	}
	cout << "End of character creation..." << endl;
}

//LOAD CHARACTER FROM FILE//////////////////////////////////////////////////
//0-Create a default character in test_file just so no exception shut down the program
//1-Ask name of file save the input
//2-Print the player's name and level
//3-Asks the User is this is the Character he wants --> Y/N
//Next step here should load the game!
//@return loaded Character Player

*/

Player Game::loadPlayer(){
	bool bValid = true;
	//input to continue loop ..assigning x as a default
	std::string str_Value = "x";

	//name of file to load from
	std::string str_filename;

	//Default character so the file called isn't empty
	Player p0 = Player("Default Character", 1, 1);

	//Character that will hold the character information
	Player p1;

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

			ia >> p1;
			cout << "Name: " << p1.getName() << " level: " << p1.getLevel() << endl;
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
	//Return character information from a file
	return p1;
}//END OF FUNCTION LOADPLAYER()

//EDIT A CHARACTER FROM A LOAD
void Game::createPlayerFromLoad(){
	int index = 0;
	int level = 0;
	std::string str_name;
	//Call the loadPlayer() function and save the player 
	Player playerUpdate = Game::loadPlayer();
	
	//For now, only can change level or name
	while (index != 3){
		//menu
		if(index == 0){
			cout << "Please select an option:--->" << endl;
			cout << "Change name----------press 1" << endl;
			cout << "Change level---------press 2" << endl;
			cout << "back-----------------press 3" << endl;
			cin >> index;
		}
		//change name
		else if (index == 1){
			cout << "Please enter a new name--->" << endl;
			cin >> str_name;
			cout << "You changed: " << playerUpdate.getName() << endl;
			playerUpdate.setName(str_name);
			cout << "For the new name of: " << playerUpdate.getName() << endl;
			index = 0;
		}
		//change level
		else if (index == 2){
			cout << "Please enter a new level -->" << endl;
			cin >> level;
			cout << "You changed level : " << playerUpdate.getLevel()<< endl;
			playerUpdate.updateLvl(level);
			cout << "Now you level up to: -->" << endl;
			playerUpdate.getLevel();
			index = 0;
		}
	}
}

//This function should ask a map from user and make the changes asked.
Map Game::loadMap(){

	bool bValid = true;
	//input to continue loop ..assigning x as a default
	std::string str_Value = "x";

	//name of file to load from
	std::string str_filename;

	//Default character so the file called isn't empty
	Map m0 = Map("", 10,10);

	//Character that will hold the character information
	Map m1;

	//Loading the file
	std::ofstream ofs("test_file");

	//printing to file
	{
		boost::archive::text_oarchive oa(ofs);
		oa << m0;
	}

	//welcome screen
	cout << "----------------------------------" << endl;
	cout << "--------------LOADING A MAP---------" << endl;
	cout << "------------------------------------\n" << endl;

	//While the user didn't press Y to continue..
	//loop this:
	while (bValid){
		cout << "Please enter a valid file name (ex: test_file) -->    " << endl;

		//getting input from user
		cin >> str_filename;
		cout << "Loading file...." << endl;

		{
			std::ifstream ifs(str_filename);
			boost::archive::text_iarchive ia(ifs);
			// read class state from archive

			//Here we should add a foreach and loop throught all the characters in the files
			//Get the player that the user wants and load it

			ia >> m1;
			cout << "Printing the map..." << endl;
			m1.toString();
			// archive and stream closed when destructors are called
		}
		cout << "Continue with this map? Enter Y or N -->" << endl;
		cin >> str_Value;
		if (str_Value.compare("Y") == 0 || str_Value.compare("y") == 0){
			cout << "Thank you!" << endl;
			cout << "Loading the game..." << endl;
			bValid = false;
		}
	}
	//Return character information from a file
	return m1;
}

//This function asks the user to edit a map
void Game::mapEditor(Map map){
	std::string str_answer;
	std::string str_campName = "default_map"; //default name if nothing
	int height;
	int width;
	int row;
	int column;
	//Map map;---passed as an argument
	int page = 0;//index for menu of map creation
	//bool b_answer = true;--can be delete.
	cout << "------------------------------------" << endl;
	cout << "---------USER MAP CREATION-----------" << endl;
	cout << "------------------------------------\n" << endl;
	cout << "Here is your template--->" << endl;
	map.toString();

	//MINI MENU - index 0
	//1-set height and width
	//2-place chests
	//3-place Player
	//4-Place NPC ennemi
	//5-Place NPC friend
	//6-entry/exit
	//7-walls
	//8-exit

	//While User doesn't exit
	while (page != 8){
		//show menu
		if (page == 0){
			cout << "--Mini Menu--" << endl;
			cout << "set height and width---press 1" << endl;
			cout << "set chests-------------press 2" << endl;
			cout << "set NPC ennemi(s)------press 3" << endl;
			cout << "set NPC friend(s)------press 4" << endl;
			cout << "set Entry/Exit---------press 5" << endl;
			cout << "set Walls--------------press 6" << endl;
			cout << "remove Walls-----------press 7" << endl;
			cout << "exit-------------------press 8" << endl;
			cin >> page;
		}
		//set a new height and width
		else if (page == 1){
			cout << "Please enter a new height: " << endl;
			cin >> height;
			cout << "Please enter a new width:" << endl;
			cin >> width;
			//----> this is illegal ---> map = Map(height, width);
			cout << "Here is the new map:" << endl;
			map.toString();

			//return to mini menu!
			page = 0;
		}
		//set chests in the map
		else if (page == 2){
			Chest chest = Chest();//this does nothing -- I don't know how to save chest
			cout << "Please enter a Row and a Column to put the chest:" << endl;
			cout << "Row-->" << endl;
			cin >> row;
			cout << "Column-->" << endl;
			cin >> column;
			//this creates an error---> map.fillCell(row, column, 'C');
			map.toString();
			cout << "Please add objects to the chest!" << endl;
			cout << "Need to add a function to save chest content and position in map" << endl;
			cout << "**Reminder** this need to be added!!!!" << endl;
			//return to mini menu!
			page = 0;
		}
		//set NPC ennemi
		else if (page == 3){
			cout << "Please enter a Row and a Column to set the NPC ennemi origin: " << endl;
			cout << "Row--->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			Enemy myNME = Enemy();//need to save this in the map
			//---> this creates an error--->map.fillCell(row, column, 'E');
			cout << "Here is the map updated!" << endl;
			map.toString();
			page = 0;
		}
		//set NPC friend
		else if (page == 4){
			cout << "Please enter a Row and a Column to set the NPC friend origin: " << endl;
			cout << "Row--->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			//map.addFriend(new Friendly("Bob", 3), row, column);
			cout << "Here is the map updated!" << endl;
			map.toString();
			page = 0;
		}
		//set entry/exit
		else if (page == 5){
			cout << "Please enter Entry door Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter Entry door Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;
			cout << "**Reminder*** Need to add entry and exit door here!!!" << endl;
			map.updateFirstStop(row, column);
			
			cout << "Please enter Exit door Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter Entry door Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;
	
			map.updateLastStop(row, column);
			map.toString();
			page = 0;
		}
		//set Walls
		else if (page == 6){
			int end = 0;
			cout << "Please enter the First cell of your wall with its row and column:" << endl;
			cout << "Row-->" << endl;
			cin >> row;
			cout << "Column--->" << endl;
			cin >> column;
			cout << "Do you want to build a vertical or horizontal wall?" << endl;
			cout << "Please enter V or H" << endl;
			cin >> str_answer;
			//if vertical
			if ((str_answer.compare("V") == 0) || (str_answer.compare("v") == 0)){
				cout << "Please enter the row you want your wall to end:--->" << endl;
				cin >> end;
				map.setRowWall(row, column, end);
				cout << "Here is the map updated" << endl;
				map.toString();
			}
			//if horizontal
			else if ((str_answer.compare("H") == 0) || (str_answer.compare("h") == 0)){
				cout << "Please enter the column you want your wall to end:--->" << endl;
				cin >> end;
				map.setColWall(column, row, end);
				cout << "Here is the map updated" << endl;
				map.toString();
			}
			//back to mini menu
			map.toString();
			page = 0;
		}
		//remove object
		else if (page == 7){
			cout << "Remove object" << endl;
			cout << "Please enter the object Row" << endl;
			cout << "Row --> " << endl;
			cin >> row;
			cout << "Please enter the object Column" << endl;
			cout << "Column --> " << endl;
			cin >> column;

			//delete map.getCell(row, column)->getContent();
			map.toString();
			page = 0;
	
			//Note: check if character to remove from character lists
		}
		else{
			cout << "This is not a valid input for the menu!" << endl;
			//return to menu
			page = 0;
		}
	}//END OF WHILE LOOP FOR MINI MENU

	//SAVE OR DON'T SAVE THE MAP
	cout << "Do you want to save the map? Y or N ---->" << endl;
	cin >> str_answer;

	//IF YES
	if ((str_answer.compare("Y") == 0) || (str_answer.compare("y") == 0)){
		if (map.validPath())
		{
			map.save(map.getName());
		}
		cout << "Before saving, we need to test the validity of the map..." << endl;
		//...
	}
	//IF NO --> USER DECIDED HE IS NOT SAVING
	else{
		cout << "We are not saving the map!" << endl;
		cout << "This is the end of the creation map ...." << endl;
	}

}