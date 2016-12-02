#pragma once
#include "stdafx.h"
#include <cstdlib>
#include "character_strategy.h"
#include "map.h"

BOOST_CLASS_EXPORT_GUID(HumanPlayerStrategy, "HumanPlayerStrategy")
BOOST_CLASS_EXPORT_GUID(HostileStrategy, "HostileStrategy")
BOOST_CLASS_EXPORT_GUID(FriendlyStrategy, "FriendlyStrategy")

const int CharacterStrategy::SPEED = 5;
const int CharacterStrategy::LBS_LIMIT = 30;
const float CharacterStrategy::LBS_PENALTY = 0.33;
const int CharacterStrategy::SIGHT_DIST = 6;

//! @return: strait line distance between two cell
int CharacterStrategy::lineDist(Cell* c1, Cell* c2)
{
	float delta_x = std::abs(c2->getCol() - c1->getCol());
	float delta_y = std::abs(c2->getRow() - c1->getRow());

	return (int) std::ceil(std::sqrt(delta_x * delta_x + delta_y * delta_y));
}

//! @return: true if inside detection distance
bool CharacterStrategy::canSee(Cell* c1, Cell* c2)
{
	return lineDist(c1, c2) <= SIGHT_DIST;
}

//! @return: a matrice of numbers. -1 is wall. Other numbers represents # of steps to access the cell from the player's position
vector<vector<int>> CharacterStrategy::graph(Map* map, Cell* dest)
{
	return map->dijkstra(dest);
}

//! @return: one of the closest cell (position) to the destination // same cell if someone is there 
Cell* CharacterStrategy::stepToward(Map* map, Cell* source, Cell* dest)
{
	int minRow = map->getHeight() + 1;
	int minCol = map->getWidth() + 1;
	int min = minRow * minCol;
	int temp;
	vector<vector<int>> distances;

	distances = graph(map, dest);

	for (Cell* c : source->getAdjacent())
	{
		temp = distances[c->getRow()][c->getCol()];

		if (temp < min && temp >= 0)
		{
			minRow = source->getRow();
			minCol = source->getCol();
			min = distances[source->getRow()][source->getCol()];
		}
	}

	return map->move(source, (*map)[minRow][minCol]);
}

//! @return: integer for speed of any game character
int CharacterStrategy::getSpeed(GameCharacter* me)
{
	return (me->getInventory()->getWeight() < LBS_LIMIT) ? SPEED : (int)(SPEED / LBS_PENALTY);
}

//!Will initiate the players menu action
//!---DESCRIPTION:
//!1- take the distance from graph to self --> return a matrice of numbers 
//!2- loop through all the cells in the map
//!3- give back the number of steps between each of elements in the map
//!4- if it is an ENNEMI, check if the range of the weapon reach him---yes? Give option to attack
//!5- if distance of 1 to a door or a chest, give option to open
//!6- Creating two stacks on each turn: 
//!7- ennemi stack that can be reached in this turn
//!8- unlockable stack that can be reached in this turn
//!9- empty both stack at the end of the turn
void HumanPlayerStrategy::turn(std::map<Placeable*, Cell*> *objects)
{
	char answer;//to get answer from user
	int bArray[3] = { 1, 1, 1 }; //all set to true, boolean array to check each action done only once per turn

	//will store ennemis/lockables close by...create list empty
	std::list<GameCharacter*> npc = list<GameCharacter*>();
	std::list<Lockable*> unlockable = list<Lockable*>();
	
	int stepsCount = 30;//getSpeed(me);//total steps available
	int turnAvailable = 3;//available turns number left...at 0, exit turn() function

	//IF PLAYER MOVE && STEPS COUNTER != 0 && TURN != OVER :: RESTART HERE
	//if player moves, all this below need to restart to find ennemis close by and chest/doors close by
	
	//step #1 
	distGraph = graph(map, (*objects)[me]);
	int i, j;//variables for the distGraph lookup
	
	// step #2
	//------------------------GET ALL ELEMENTS NEAR PLAYER--------this code repeats below in move------
	// iterator to go see each cell content
	// The objects are a pair. Placeable is the key and Cell is the value
	for (std::pair<Placeable*, Cell*> p : *objects)
	{
		//Placeable* temp = p.first;
		//Check if the object is a GameCharacter----yes? it is an ENNEMI or a FRIEND
		if (GameCharacter *g = dynamic_cast<GameCharacter*>(p.first))
		{
			//get the i row # and the j column # of the GameCharacter
			i = p.second->getRow();
			j = p.second->getCol();
			
			//#step 3
			//compare it with the matrix of distance to see if close to character--- yes? save it in the stack
			if (distGraph[i][j] > 0 && distGraph[i][j] < 4){
				npc.push_back(g);
				std::cout << "a player is near you! " << endl;
			}
		}
		else if (Lockable *lk = dynamic_cast<Lockable*>(p.first)){

			//get the lockable object distance on map
			i = p.second->getRow();
			j = p.second->getCol();

			//#step 3
			//you can unlock chests or doors at 1 step distance only
			if (distGraph[i][j] == 1){
				unlockable.push_back(lk);
				std::cout << "a lockable is near you! " << endl;
			}
		}
	}
	//----------------------LOOP TO GET ELEMENTS ENDS HERE

	//At this point, we have two lists with lockables and ennemis/friends

	//---------------------ERASE MAP AND OTHER CONTENT
	system("cls");
	//----------------------PRINT UPDATED MAP
	std::cout << map->toString2();

	//----------------------DIPLAY POSSIBLE ACTIONS TO PLAYER WHILE THE TURN IS NOT OVER
	//----------------------turnAvailable = 0 is the end
	while (turnAvailable != 0){
		std::cout << "--------------------PLAY!----------------------" << endl;
		std::cout << "YOU HAVE ---------"<<turnAvailable<<"----- TURN AVAILABLE!" << endl;
		std::cout << "YOU HAVE ---------" << stepsCount << "---- STEPS AVAILABLE!" << endl;
		//Ennemies in the list?

		if (!npc.empty() && (bArray[0] == 1)){
			//display the possibility of the attack
			std::cout << "ATTACK -------------- PRESS 1" << endl;
		}
		//chests/doors in the list?
		if (!unlockable.empty() && bArray[1] == 1){
			//display the possibility of the unlock door
			std::cout << "UNLOCK -------------- PRESS 2" << endl;
		}
		//always able to equip/unequip...so always display it
		if (bArray[2] == 1){
			std::cout << "EQUIP/UNEQUIP ------- PRESS 3" << endl;
		}
		//always to display toggle
		std::cout << "TOGGLE BETWEEN OBJ. - PRESS 4" << endl;
		//always able to end his turn...so always display it
		std::cout << "END TURN?------------ PRESS 5" << endl;
		//-------------------DISPLAY ENDS HERE--------------------------

		//get answer
		std::cin >> answer;
		int choseThis = 1;//other choice for user
		//------------------------CHECK INPUT AND DISPLAY POSSIBILITES + CALL TO ACTION
		//------------------ATTACK!
		//bArray has values of 0 or 1---can attack only once
		if ((answer == 49) && (bArray[0] == 1)){

			//---------------------ERASE MAP AND OTHER CONTENT

			system("cls");
			//----------------------PRINT UPDATED MAP
			std:: cout << map->toString2();

			GameCharacter *temp = NULL;
			int attackInput = 0;
			std::cout << "Choose the NPC to attack!!--->" << endl;
			for (int i = 0; i < npc.size(); i++){
				temp = npc.front();//get first element

				//print what the first element contains
				std::cout << "NPC at [ " << (*objects)[temp]->getRow() << ", " << (*objects)[temp]->getCol() << " ]----> PRESS " << i << endl;

				npc.pop_front();//pop the first element
				npc.push_back(temp);//put it at the end of the list
			}
			bArray[0] = 0;//only can attack once---this is a boolean array

			//-------------ATTACK THE CHOSEN NPC
			std::cin >> attackInput;

			//---------------------ERASE MAP AND OTHER CONTENT
			system("cls");
			//----------------------PRINT UPDATED MAP
			std::cout << map->toString2();
			//Find the NPC to attack----loop throught the list
			//to check if attack is working
			bool isWorking = false;
			for (int i = 0; i < npc.size(); i++){
				temp = npc.front();
				if (attackInput == i){

					//attack the npc!!!!
					std::cout << "NPC info before: ---> HP: " << temp->getHp()  <<", Lvl " << temp->getLevel()<< endl;
					me->attack(temp, lineDist((*objects)[me], (*objects)[temp]));
					std::cout << "you have attacked! " << endl;
					std::cout << "NPC info after: ---> HP: " << temp->getHp() << ", Lvl " << temp->getLevel() << endl;
					turnAvailable--;
					isWorking = true;
				}
				else if ((i == (npc.size() - 1)) && !isWorking){//if at the end but nothing has been attacked
					std::cout << "you maybe entered the wrong input ..." << endl;
					std::cout << "I am substracting from a turn anyway...." << endl;
					turnAvailable--;
				}
			}
		}//end of attack

		//----------------UNLOCK!
		//if choose to unlock something
		else if (answer == 50 && bArray[1] == 1){

			//---------------------ERASE MAP AND OTHER CONTENT
			system("cls");
			//----------------------PRINT UPDATED MAP
			std::cout << map->toString2();

			Lockable *temp;
			choseThis = 0;//reset variable
			int unlockThis = 0;
			std::cout << "Choose what to unlock!!--->" << endl;
			for (int k = 0; k < unlockable.size(); k++){
				temp = unlockable.front();
				if (temp->isLocked()){
					std::cout << "Locked object at [" << (*objects)[temp]->getRow() << ", " << (*objects)[temp]->getCol() << "]----> PRESS " << choseThis << endl;
				}
				else{
					std::cout << "Unlocked object at [" << (*objects)[temp]->getRow() << ", " << (*objects)[temp]->getCol() << "]----> PRESS " << choseThis << endl;
				}
				
				unlockable.pop_front();//pop the first element
				unlockable.push_back(temp);//put it at the end of the list
				choseThis++;//to get a number to press
			}

			bArray[1] = 0;
			std::cin >> unlockThis;

			//to check if chest is open or not
			unordered_set<Item*> checkContent = unordered_set<Item*>();

			bool isWorking = false;
			for (int i = 0; i < unlockable.size(); i++){
				temp = unlockable.front();
				if (unlockThis == i){

					//unlock object!!!!!
					checkContent = me->unlock(unlockable.front());//----??? is this ok???
					
					if (!checkContent.empty()){
						std::cout << "the chest is unlocked! Here is the content of the chest:" << endl;
						//Printing elements of the chest and 
						cout << temp->toString();
						std::cout << "Here is the content of your backpack now!" << endl;
						cout << me->toString();
					}
					else{
						std::cout << "the chest is empty" << endl;
					}
					turnAvailable--;
					isWorking = true;
				}
				else if ((i == npc.size() - 1) && !isWorking){//if at the end but nothing has been attacked
					std::cout << "you maybe entered the wrong input ..." << endl;
					std::cout << "I am substracting from a turn anyway...." << endl;
					turnAvailable--;
				}
			}

		}
		//---------------EQUIP!
		//if choose to  equip/unequip
		else if (answer == 51 && bArray[2] == 1){

			//---------------------ERASE MAP AND OTHER CONTENT
			system("cls");
			//----------------------PRINT UPDATED MAP

			std::cout<<map->toString2();
			int pressed = 0;
			bool bEquip = true;
			//get objects in backpack!
			unordered_set<Item*> inBackpack = me->getInventory()->getBackPack();

			//get the vector of pointers to the equipped items of the player
			vector<Equipment*> equip = me->getInventory()->getAllEquipment();
			Equipment* tempEquip; //to get the equipment and print them
			vector<Equipment*> backpack;
			//if user didn't enter a good value, the inventory is reprinted and we start over
			while (bEquip){
				std::cout << "\n_______________________________EQUIP/UNEQUIP_________________________________________\n";
				std::cout << "What do you want to equip? ---->" << endl;
				std::cout << "Equipped items: " << endl;
				//print all the equipped items to display on screen only
				for (int i = 0; i < equip.size(); i++){
					tempEquip = equip[i];
					std::cout << tempEquip->toString() << endl;
				}
				std::cout << "Backpack items: " << endl;
				//display what is in the backpack and give an input number to change
				for (Item* i : inBackpack){
					//check if it is an equipment object, yes put in the vector list
					if (Equipment *eq = dynamic_cast<Equipment*>(i)){
						backpack.push_back(eq);
					}
				}
				int counter = 0;//count # of elements in backpack to show on screen

				//display on screen
				//for (Equipment* i : backpack){
					//std::cout << i->toString() << "            -----PRESS " << counter << endl;
					//counter++;
				//}
				for (int k = 0; k < backpack.size();k++){
					std::cout << backpack[k]->toString() << "               -----PRESS " << k << endl;
				}

				//get answer from user
				std::cin >> pressed;

				//go throught the backpack, found the item the user wants and equip it
				for (int k = 0; k < backpack.size(); k++){
					if (pressed == k){//if the element is found
						me->equip(backpack[k]);
						bEquip = false;

						system("cls");
						std::cout << map->toString2();
						std::cout << "The item has been equipped!" << endl;
					} 
					//if it's the last item but nothing has been equipped
					else if ((i == (backpack.size() - 1)) && (bEquip == true)){
						std::cout << "Nothing has been equipped...starting again..." << endl;
					}
				}
			}//end of the bEquip loop

			//one less turn available
			turnAvailable--;
			//boolean array -- so the option to equip appears only once
			bArray[2] = 0;
		}//-----------------------------------------------END OPTION TO EQUIP

		//-----------------------------------------------TOGGLE BETWEEN OBJECTS IN THE ROOM
		//this option doesn't substract from your turn, but it is available only during your turn
		else if (answer == 52){

			//---------------------ERASE MAP AND OTHER CONTENT
			system("cls");
			//----------------------PRINT MAP
			std::cout << map->toString2();
			//---------------------PRINT INFO
			//------------------------GO THROUGHT ALL ELEMENTS IN tHE ROOM------
			int nextAnswer = 0;//user input
			// iterator to go see each cell content
			// The objects are a pair. Placeable is the key and Cell is the value
			for (std::pair<Placeable*, Cell*> p : *objects)
			{
				//Placeable* temp = p.first;
				//Check if the object is a GameCharacter----yes? it is an ENNEMI or a FRIEND
				if (GameCharacter *g = dynamic_cast<GameCharacter*>(p.first))
				{
					//get the i row # and the j column # of the GameCharacter
					i = p.second->getRow();
					j = p.second->getCol();

					//print the object + name + position + content to screen
					std::cout << "Name: " << g->getName() << " at position [ " << i << ", " << j << " ]" << endl;
					std::cout << "information: " << g->toString() << endl;
				}
				else if (Lockable *lk = dynamic_cast<Lockable*>(p.first)){

					//get the lockable object distance on map
					i = p.second->getRow();
					j = p.second->getCol();

					//print the object + name + position + content to screen
					std::cout << "Name : " << lk->getClassName() << " at position [ " << i << ", " << j << " ]" << endl;
					std::cout << "locked? : ";
					if (lk->isLocked()){
						std::cout << "yes" << endl;
					}
					else{
						std::cout << "no" << endl;
					}

					//if the object is a chest, show content
					if (Chest *ch = dynamic_cast<Chest*>(p.first)){
						cout << "content : " << ch->toString() << endl;
					}
				}
				else {
					continue;
				}
				std::cout << "PRESS 9 to get next object name and content." << endl;
				std::cin >> nextAnswer;
				system("cls");
				std::cout<<map->toString2();
			}
			//----------------------LOOP TO GET ELEMENTS ENDS HERE

		}


		//----------------------------------------------STOP THE CHARACTER TURN OPTION
		else if (answer == 53){
			//this will exit the biggest loop and terminate the function
			//---------------------ERASE MAP AND OTHER CONTENT
			system("cls");
			//----------------------PRINT UPDATED MAP
			std::cout << map->toString2();
			//exit
			turnAvailable = 4;
		}
		//-----------------------------------PLAYER WANTS TO MOVE
		else{
			//string s_answer = std::to_string(answer);
			//char s = (char)answer;
			bool moved = true;
			//check if the input is a valid direction
			bool validDirection = Direction::valid(answer);

			//here need to check if the cell changed, if not changed then it is not taking it's steps away.
			while (moved){

				//if the input is a valid direction and the stepscount is bigger than 0
				//move the character and reduce it's steps count
				if (validDirection && (stepsCount > 0)){

					//move the character!!!!
					(*objects)[me] = map->move((*objects)[me], *Direction::getMap()[answer]);

					//---------------------ERASE MAP AND OTHER CONTENT
					system("cls");
					//----------------------PRINT UPDATED MAP
					std::cout << map->toString2();

					//cout << "Character moved and the map reprints it`s movements!!!!" << endl;
					stepsCount--;

					//********************************************************************************
					//HERE NEED TO RESCAN THE ROOM FOR OBJECTS AND REDO THE TWO LISTS OF LOCKABLES AND NPC
					
					//redo the distgraph 
					distGraph = graph(map, (*objects)[me]);

					//clear the npc and unlockable list
					npc.clear();
					unlockable.clear();

					//------------------------GET ALL ELEMENTS NEAR PLAYER--------------
					// iterator to go see each cell content
					// The objects are a pair. Placeable is the key and Cell is the value
					for (std::pair<Placeable*, Cell*> p : *objects)
					{
						//Placeable* temp = p.first;
						//Check if the object is a GameCharacter----yes? it is an ENNEMI or a FRIEND
						if (GameCharacter *g = dynamic_cast<GameCharacter*>(p.first))
						{
							//get the i row # and the j column # of the GameCharacter
							i = p.second->getRow();
							j = p.second->getCol();

							//TESTING FOR DEBUGGING
							//std::cout << "just tchecking if this is running" << endl;
							//std::cout << "character at [ " << i << ", " << j <<" ]"<< endl;
							//std::cout << "player is at [" << (*objects)[me]->getRow() << ", " << (*objects)[me]->getCol() <<" ]"<< endl;
							//std::cout << "distGraph number is : " << distGraph[i][j] << endl;
							
							//#step 3
							//compare it with the matrix of distance to see if close to character--- yes? save it in the stack
							if (distGraph[i][j] > 0 && distGraph[i][j] <= 4){
								npc.push_back(g);
								//std::cout << "a player is near you! " << endl;
							}
						}
						else if (Lockable *lk = dynamic_cast<Lockable*>(p.first)){

							//get the lockable object distance on map
							i = p.second->getRow();
							j = p.second->getCol();

							//TESTING FOR DEBUGGING
							//std::cout << "just tchecking if this is running" << endl;
							//std::cout << "lockable at [ " << i << ", " << j <<" ]"<< endl;
							//std::cout << "player is at [" << (*objects)[me]->getRow() << ", " << (*objects)[me]->getCol() <<" ]"<< endl;
							//std::cout << "distGraph number is : " << distGraph[i][j] << endl;

							//#step 3
							//you can unlock chests or doors at 1 step distance only
							if (lineDist((*objects)[me], (*objects)[lk]) == 1){
								unlockable.push_back(lk);
								std::cout << "a lockable is near you! " << endl;
							}
						}
					}
					moved = false;
					//----------------------LOOP TO GET ELEMENTS ENDS HERE
					//**************************************************************************
				}
				else if (!validDirection){
					std::cout << "You printed : " << answer << endl;
					std::cout << "Input is invalid! Try something else" << endl;
					moved = false;
				}
				else if (stepsCount <= 0){
					std::cout << "Character is not allowed to move anymore!" << endl;
					turnAvailable--;
					moved = false;
				}
			}
		}//end of the move input
	}//end of while turnAvailable != 0
	std::cout << "**********************END OF YOUR TURN! NPC's TURN NOW!******************" << endl;

}//end of the turn function

//! @ return: number to adjust HP...not HP itself is returned
//! modifyHp sends the variation of HP, not the new HP
int HumanPlayerStrategy::takeDamage(GameCharacter* opponent, int damageValue)
{
	int damage = std::max(1, damageValue);

	return me->modifyHp(damage);
}


//!Hostile Ennemy stragtegy. Will seek the player if in a radius of 6 cells
//!and attack him as soon as he is in range, depending on his weapon.
void HostileStrategy::turn(std::map<Placeable*, Cell*> *objects)
{
	int i;

	int range = me->getRange(); //get weapon range

	int visibility = std::max(range, SIGHT_DIST);

	bool walking = true;

	std::map<Placeable*, Cell*>::iterator iter;
	Cell* temp = nullptr;
	Cell* myCell = (*objects)[me];
	Cell* playerCell = (*objects)[map->getPlayer()];

	distGraph = graph(map, playerCell);

	while (walking)
	{
		i = getSpeed(me);//speed is 3 now because there is no weight now.

		//cansee() give two cells - calculate linear distance, return true or false
		if (!canSee(myCell, playerCell))
		{
			while (i > 0 && walking)//if my speed is bigger than 0 and I am still walking
			{
				//record the cell I am on
				temp = myCell;

				//loop while temp == myCell...
				//--if the movement is possible, the cell value will be different
				//--if the movement is impossible, the cell value returned is the same.
				do
				{
					//get a random direction form randDir()
					myCell = map->move(myCell, Direction::randDir());
					(*objects)[me] = myCell;//me is a placebale index value and myCell is the value attached to the index 
					//if the player is in the attack zone, stop to attack
					if (canSee(myCell, playerCell))
					{
						walking = false;
						break;
					}
				} while (temp == myCell);//while the cell I am on didn;t change...

				i--;
			}
		}

		//am I the the player and I can still move and my cell is not null --- see through walls
		if (canSee(myCell, playerCell) && i > 0 && temp != NULL)
		{
			while (i > 0)
			{
				i--;
				//need to fix stepToward! not working, asks oliver
				myCell = map->move(myCell, stepToward(map, myCell, playerCell));
				(*objects)[me] = myCell;//Update the value

				//lineDist() -- strait line distance between ennemi and player
				// range is the weapon
				// stop walking to attack player
				if (lineDist(myCell, playerCell) <= range)
				{
					walking = false;
					break;
				}
			}
		}
	}

	//strait line distance
	if (lineDist(myCell, playerCell) <= range)
	{
		me->attack(map->getPlayer(), lineDist(myCell, playerCell));
	}
}

//! same as takeDamage of others..return an integer to change HP, not the new HP itself
int HostileStrategy::takeDamage(GameCharacter* attacker, int damageValue)
{
	int damage = std::max(1, damageValue);

	return me->modifyHp(damage);
}

//! Passive friendly strategy. Simply follows the player.
//! See HostileStrategy for description of function --- nearly the same
void FriendlyStrategy::turn(std::map<Placeable*, Cell*> *objects)
{
	int i;

	//Set to accomodate for an active friendly NPC in battles,
	//but not implemented yet.
	int range = me->getRange();

	int visibility = std::max(range, SIGHT_DIST);

	bool walking = true;

	std::map<Placeable*, Cell*>::iterator iter;
	Cell* temp = nullptr;
	Cell* myCell = (*objects)[me];
	Cell* playerCell = (*objects)[map->getPlayer()];

	distGraph = graph(map, playerCell);

	while (walking)
	{
		i = getSpeed(me);

		if (!canSee(myCell, playerCell))
		{
			while (i > 0 && walking)
			{
				temp = myCell;

				do
				{
					myCell = map->move(myCell, Direction::randDir());
					(*objects)[me] = myCell;//update value
					if (canSee(myCell, playerCell))
					{
						walking = false;
						break;
					}
				} while (temp == myCell);

				i--;
			}
		}

		if (canSee(myCell, playerCell) && i > 0 && temp != NULL)
		{
			while (i > 0)
			{
				i--;
				myCell = map->move(myCell, stepToward(map, myCell, playerCell));
				(*objects)[me] = myCell;//update value!
				if (lineDist(myCell, playerCell) <= range)
				{
					walking = false;
					break;
				}
			}
		}
	}
}

//Friends will become actively hostile if hit by the player.
int FriendlyStrategy::takeDamage(GameCharacter* attacker, int damageValue)
{
	int damage = std::max(1, damageValue);

	if (attacker == map->getPlayer())
	{
		me->modifyHp(damage);
		me->setStrategy(new HostileStrategy(me));
		this->~FriendlyStrategy();
	}

	return me->modifyHp(damage);
}
