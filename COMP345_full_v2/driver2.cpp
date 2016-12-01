// COMP345_full_v0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "map.h"
#include "game.h"
#include "campain.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

void testList()
{
	map<int, std::string> list = listFiles(ASSETS_PATH + "items");

	for (int i = 1; i <= list.size(); i++)
	{
		cout << to_string(i) << ". " << list[i] << endl;
	}
}

void testSave1()
{
	int i;
	int level = 1;

	Player p1 = Player("player1", 1, 2);
	Player p2 = Player("player2", 1, 4);

	vector<Equipment*> equip1 = vector<Equipment*>();
	vector<Equipment*> equip2 = vector<Equipment*>();

	Helmet* head1 = new Helmet("helmet1");
	equip1.push_back(head1);
	Helmet* head2 = new Helmet("helmet2");
	equip2.push_back(head2);

	Cuirass* cuirass1 = new Cuirass("cuirass1");
	equip1.push_back(cuirass1);
	Cuirass* cuirass2 = new Cuirass("cuirass2");
	equip2.push_back(cuirass2);

	Boots* boots1 = new Boots("boots1");
	equip1.push_back(boots1);
	Boots* boots2 = new Boots("boots2");
	equip2.push_back(boots2);

	Ring* ring1 = new Ring("ring1");
	equip1.push_back(ring1);
	Ring* ring2 = new Ring("ring2");
	equip2.push_back(ring2);

	Belt* belt1 = new Belt("belt1");
	equip1.push_back(belt1);
	Belt* belt2 = new Belt("belt2");
	equip2.push_back(belt2);

	Shield* shield1 = new Shield("shield1");
	equip1.push_back(shield1);
	Shield* shield2 = new Shield("shield2");
	equip2.push_back(shield2);

	Weapon* weapon1 = new Weapon("weapon1", 1, 1, 8);
	equip1.push_back(weapon1);
	Weapon* weapon2 = new Weapon("weapon2", 1, 1, 8);
	equip2.push_back(weapon2);

	for (Equipment* e: equip1)
	{
		e->updateLvl(5);
		//cout << e->toString() << endl;
	}

	for (Equipment* e : equip2)
	{
		e->updateLvl(1);
		//cout << e->toString() << endl;
	}

	head1->save(head1->getName());
	cuirass1->save(cuirass1->getName());
	boots1->save(boots1->getName());
	ring1->save(ring1->getName());
	belt1->save(belt1->getName());
	shield1->save(shield1->getName());
	weapon1->save(weapon1->getName());

	head2->load(head1->getName());
	cuirass2->load(cuirass1->getName());
	boots2->load(boots1->getName());
	ring2->load(ring1->getName());
	belt2->load(belt1->getName());
	shield2->load(shield1->getName());
	weapon2->load(weapon1->getName());
	/*
	for (Equipment* e : equip2)
	{
		cout << e->toString() << endl;
	}
	*/
}

void testSave2()
{
	Player p1 = Player("player1", 1, 2);
	Player p2 = Player("player2", 1, 4);

	vector<Equipment*> equip1 = vector<Equipment*>();
	vector<Equipment*> equip2 = vector<Equipment*>();

	Helmet* head1 = new Helmet("helmet1");
	equip1.push_back(head1);
	Helmet* head2 = new Helmet("helmet2");
	equip2.push_back(head2);

	Cuirass* cuirass1 = new Cuirass("cuirass1");
	equip1.push_back(cuirass1);
	Cuirass* cuirass2 = new Cuirass("cuirass2");
	equip2.push_back(cuirass2);

	Boots* boots1 = new Boots("boots1");
	equip1.push_back(boots1);
	Boots* boots2 = new Boots("boots2");
	equip2.push_back(boots2);

	Ring* ring1 = new Ring("ring1");
	equip1.push_back(ring1);
	Ring* ring2 = new Ring("ring2");
	equip2.push_back(ring2);

	Belt* belt1 = new Belt("belt1");
	equip1.push_back(belt1);
	Belt* belt2 = new Belt("belt2");
	equip2.push_back(belt2);

	Shield* shield1 = new Shield("shield1");
	equip1.push_back(shield1);
	Shield* shield2 = new Shield("shield2");
	equip2.push_back(shield2);

	Weapon* weapon1 = new Weapon("weapon1", 1, 1, 8);
	equip1.push_back(weapon1);
	Weapon* weapon2 = new Weapon("weapon2", 1, 1, 8);
	equip2.push_back(weapon2);


	for (Equipment* e : equip1)
	{
		e->updateLvl(p1.getLevel());
		p1.addToPack(e);
	}


	for (Equipment* e : equip2)
	{
		e->updateLvl(p2.getLevel());
		p1.equip(e);
	}

	//cout << p1.toString() << endl << endl;

	p1.save(p1.getName());

	//cout << p2.toString();

	p2.save("player2");


}

void testSave3()
{
	Chest c1 = Chest();
	Chest c2 = Chest();

	vector<Item*> equip1 = vector<Item*>();
	vector<Item*> equip2 = vector<Item*>();

	Helmet* head1 = new Helmet("helmet1");
	equip1.push_back(head1);
	Helmet* head2 = new Helmet("helmet2");
	equip2.push_back(head2);

	Cuirass* cuirass1 = new Cuirass("cuirass1");
	equip1.push_back(cuirass1);
	Cuirass* cuirass2 = new Cuirass("cuirass2");
	equip2.push_back(cuirass2);

	Boots* boots1 = new Boots("boots1");
	equip1.push_back(boots1);
	Boots* boots2 = new Boots("boots2");
	equip2.push_back(boots2);

	Ring* ring1 = new Ring("ring1");
	equip1.push_back(ring1);
	Ring* ring2 = new Ring("ring2");
	equip2.push_back(ring2);

	Belt* belt1 = new Belt("belt1");
	equip1.push_back(belt1);
	Belt* belt2 = new Belt("belt2");
	equip2.push_back(belt2);

	Shield* shield1 = new Shield("shield1");
	equip1.push_back(shield1);
	Shield* shield2 = new Shield("shield2");
	equip2.push_back(shield2);

	Weapon* weapon1 = new Weapon("weapon1", 1, 1, 8);
	equip1.push_back(weapon1);
	Weapon* weapon2 = new Weapon("weapon2", 1, 1, 8);
	equip2.push_back(weapon2);

	KeyItem* key1 = new KeyItem("key1", 0);
	equip1.push_back(key1);
	KeyItem* key2 = new KeyItem("key2", 0);
	equip2.push_back(key2);

	for (Item* e : equip1)
	{
		e->updateLvl(4);
		c1.addItem(e);
	}

	//cout << c1.toString() << endl;

	for (Item* e : equip2)
	{
		e->updateLvl(8);
		c2.addItem(e);
	}

	//cout << c2.toString() << endl;

	//CALL UPDATE_BONUS WHEN LOAD CHARACTER 

	{
		std::ofstream ofs(ASSETS_PATH + "items\\chest1");
		boost::archive::text_oarchive oa(ofs);
		oa << c1;
	}

	{
		std::ifstream ifs(ASSETS_PATH + "items\\chest1");
		boost::archive::text_iarchive ia(ifs);
		ia >> c2;
	}

	{
		std::ofstream ofs2(ASSETS_PATH + "items\\chest2");
		boost::archive::text_oarchive oa2(ofs2);
		oa2 << c2;
	}
}

void testSave4()
{
	Chest c1 = Chest();
	Chest c2 = Chest();

	vector<Item*> equip1 = vector<Item*>();
	vector<Item*> equip2 = vector<Item*>();

	Helmet* head1 = new Helmet("helmet1");
	equip1.push_back(head1);
	Helmet* head2 = new Helmet("helmet2");
	equip2.push_back(head2);

	Cuirass* cuirass1 = new Cuirass("cuirass1");
	equip1.push_back(cuirass1);
	Cuirass* cuirass2 = new Cuirass("cuirass2");
	equip2.push_back(cuirass2);

	Boots* boots1 = new Boots("boots1");
	equip1.push_back(boots1);
	Boots* boots2 = new Boots("boots2");
	equip2.push_back(boots2);

	Ring* ring1 = new Ring("ring1");
	equip1.push_back(ring1);
	Ring* ring2 = new Ring("ring2");
	equip2.push_back(ring2);

	Belt* belt1 = new Belt("belt1");
	equip1.push_back(belt1);
	Belt* belt2 = new Belt("belt2");
	equip2.push_back(belt2);

	Shield* shield1 = new Shield("shield1");
	equip1.push_back(shield1);
	Shield* shield2 = new Shield("shield2");
	equip2.push_back(shield2);

	Weapon* weapon1 = new Weapon("weapon1", 1, 1, 8);
	equip1.push_back(weapon1);
	Weapon* weapon2 = new Weapon("weapon2", 1, 1, 8);
	equip2.push_back(weapon2);

	KeyItem* key1 = new KeyItem("key1", 0);
	equip1.push_back(key1);
	KeyItem* key2 = new KeyItem("key2", 0);
	equip2.push_back(key2);

	for (Item* i : equip1)
	{
		i->save(i->getName());
	}

	for (Item* i : equip2)
	{
		i->save(i->getName());
	}

	/*
	void save(std::string filename)
	{
	std::ofstream ofs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_oarchive oa(ofs);
	oa << *this;
	}

	void load(std::string filename)
	{
	std::ifstream ifs(ASSETS_PATH + "items\\" + filename);
	boost::archive::text_iarchive ia(ifs);
	ia >> *this;
	}
	*/
}

void testSave5()
{
	cout << Dice::roll(1, 6) << endl;
	cout << Dice::roll(1, 6) << endl;
	cout << Dice::roll(1, 6) << endl;
	cout << Dice::roll(1, 6) << endl;
}

void testSave6()
{
	Enemy e1 = Enemy("enemy1", 1, 0);
	Friendly f1 = Friendly("friend2", 1, 0);

	vector<Equipment*> equip1 = vector<Equipment*>();
	vector<Equipment*> equip2 = vector<Equipment*>();

	Helmet* head1 = new Helmet("helmet3");
	equip1.push_back(head1);
	Helmet* head2 = new Helmet("helmet4");
	equip2.push_back(head2);

	Cuirass* cuirass1 = new Cuirass("cuirass3");
	equip1.push_back(cuirass1);
	Cuirass* cuirass2 = new Cuirass("cuirass4");
	equip2.push_back(cuirass2);

	Boots* boots1 = new Boots("boots3");
	equip1.push_back(boots1);
	Boots* boots2 = new Boots("boots4");
	equip2.push_back(boots2);

	Ring* ring1 = new Ring("ring3");
	equip1.push_back(ring1);
	Ring* ring2 = new Ring("ring4");
	equip2.push_back(ring2);

	Belt* belt1 = new Belt("belt3");
	equip1.push_back(belt1);
	Belt* belt2 = new Belt("belt4");
	equip2.push_back(belt2);

	Shield* shield1 = new Shield("shield3");
	equip1.push_back(shield1);
	Shield* shield2 = new Shield("shield4");
	equip2.push_back(shield2);

	Weapon* weapon1 = new Weapon("weapon3", 1, 1, 8);
	equip1.push_back(weapon1);
	Weapon* weapon2 = new Weapon("weapon4", 1, 1, 8);
	equip2.push_back(weapon2);

	KeyItem* key1 = new KeyItem("key3", 0);
	equip1.push_back(weapon1);
	KeyItem* key2 = new KeyItem("key4", 0);
	equip2.push_back(weapon2);


	for (Equipment* e : equip1)
	{
		e1.equip(e);
	}


	for (Equipment* e : equip2)
	{
		f1.addToPack(e);
	}

	//cout << e1.toString();
	//cout << f1.toString();


	e1.save(e1.getName());

	f1.save(f1.getName());

}

void testSave7()
{
	Map* myMap = new Map("map1", 15, 20);
	
	Player myPlayer;
	Chest myChest;
	Enemy myEnemy;
	Friendly myFriend;
	
	myPlayer.load("player1");
	myChest.load("chest1");
	myEnemy.load("enemy1");
	myFriend.load("friend2");

	/*
	Player myPlayer = Player::sLoad("player1");
	Chest myChest = Chest::sLoad("chest1");
	Enemy myEnemy = Enemy::sLoad("enemy1");
	Friendly myFriend = Friendly::sLoad("friend2");
	*/
	cout << myEnemy.toString();
	cout << myFriend.toString();

	myMap->setRowWall(10, 0, 18);
	myMap->setColWall(5, 1, 13);
	
	myMap->updateFirstStop(0, 0);
	myMap->updateLastStop(11, 0);

	cout << "inserted: " << myMap->addToCell((Placeable*) new Door(), 0, 5) << endl << endl;

	cout << "inserted: " << myMap->addToCell((Placeable*)&myChest, 0, 13) << endl << endl;
	cout << "inserted: " << myMap->addToCell((Placeable*)&myEnemy, 12, 10) << endl << endl;
	cout << "inserted: " << myMap->addToCell((Placeable*)&myFriend, 4, 2) << endl << endl;

	cout << endl << myMap->toString();
	
	//myMap.save("map1");
}

void testSave8()
{
	Map* myMap = new Map("map1", 15, 20);

	Cell* pCell = NULL;
	Player *myPlayer = new Player();
	Chest myChest;
	Enemy myEnemy;
	Friendly myFriend;

	myPlayer->load("player1");
	myChest.load("chest1");
	myEnemy.load("enemy1");
	myFriend.load("friend2");

	/*
	Player myPlayer = Player::sLoad("player1");
	Chest myChest = Chest::sLoad("chest1");
	Enemy myEnemy = Enemy::sLoad("enemy1");
	Friendly myFriend = Friendly::sLoad("friend2");
	*/
	cout << myEnemy.toString();
	cout << myFriend.toString();

	myMap->setRowWall(10, 0, 18);
	myMap->setColWall(5, 1, 13);

	myMap->updateFirstStop(0, 0);
	myMap->updateLastStop(11, 0);

	cout << "inserted: " << myMap->addToCell((Placeable*) new Door(), 0, 5) << endl << endl;

	cout << "inserted: " << myMap->addToCell((Placeable*)&myChest, 0, 13) << endl << endl;
	cout << "inserted: " << myMap->addToCell((Placeable*)&myEnemy, 12, 10) << endl << endl;
	cout << "inserted: " << myMap->addToCell((Placeable*)&myFriend, 4, 2) << endl << endl;

	//cout << endl << myMap->toString2() << endl;



	//cout << endl<< endl << myMap->printGraph();

	//cout << endl << endl << myMap->toString2();
	//cout << endl << (*myMap)[0][0]->isEmpty();

	//Map aMap = *myMap;

	//aMap.save("map1");

	cout << myMap->start(myPlayer);

	pCell = myMap->getBegin();
	Cell* exit = myMap->getExit();

	char dir;
	map<char, const Direction*> keyMap = Direction::getMap();
	
	for (int j = 0; j < 20; j++)
	myPlayer->attack(&myEnemy, 1);

	while (pCell != exit)
	{
		do{
			cout << "Enter a direction: ";
			cin >> dir;

		} while (!Direction::valid(dir));

		pCell = myMap->move(pCell, *keyMap[dir]);

		cout << endl << endl << myMap->toString2();
		Game aGame = Game();
		aGame.display(myPlayer);
	}	

	
}

void testSave9()
{
	Map* myMap = new Map("map1", 15, 20);

	Cell* pCell = NULL;
	Player *myPlayer = new Player();
	Chest myChest;
	Enemy myEnemy;
	Friendly myFriend;

	myPlayer->load("player1");
	myChest.load("chest1");
	myEnemy.load("enemy1");
	myFriend.load("friend2");

	/*
	Player myPlayer = Player::sLoad("player1");
	Chest myChest = Chest::sLoad("chest1");
	Enemy myEnemy = Enemy::sLoad("enemy1");
	Friendly myFriend = Friendly::sLoad("friend2");
	*/
	//cout << myEnemy.toString();
	//cout << myFriend.toString();

	myMap->setRowWall(10, 0, 18);
	myMap->setColWall(5, 1, 13);

	myMap->updateFirstStop(0, 0);
	myMap->updateLastStop(11, 0);

	myMap->addToCell((Placeable*) new Door(), 0, 5);

	myMap->addToCell((Placeable*)&myChest, 0, 13);
	myMap->addToCell((Placeable*)&myEnemy, 12, 10);
	myMap->addToCell((Placeable*)&myFriend, 4, 2);

	//cout << endl << myMap->toString2() << endl;

	//Game game = Game(myMap, myPlayer);
}

void runGame(Map* myMap, Player* myPlayer)
{
	Cell* pCell = NULL;

	myMap->start(myPlayer);

	pCell = myMap->getBegin();
	Cell* exit = myMap->getExit();

	char dir;
	map<char, const Direction*> keyMap = Direction::getMap();

	//myPlayer->attack(&myEnemy, 5);

	while (pCell != exit)
	{
		do
		{
			cout << "Enter a direction: ";
			cin >> dir;
		} while (!Direction::valid(dir));

		pCell = myMap->move(pCell, *keyMap[dir]);

		cout << endl << endl << myMap->toString2();
		Game aGame = Game();
		aGame.display(myPlayer);
	}
}

void reboot()
{
	testSave2();
	testSave3();
	testSave4();
	testSave6();
}


//Wrong map 1, horizontal wall on the way to exit.
void wrongMap1()
{
	Map* wMap1 = new Map("wmap1", 10, 10);
	wMap1->setRowWall(5, 0, 9);
	cout << endl << wMap1->toString2() << endl;
}

//Wrong map 2, chest not accesseble with a key. (how to lock door and put key in chest)
void wrongMap2()
{
	Map* wMap2 = new Map("wmap2", 10, 10);
	Chest wChest;
	Door wDoor;
	wMap2->setRowWall(5, 0, 4);
	wMap2->setRowWall(5, 6, 9);
	wMap2->addToCell((Placeable*)&wDoor, 5, 5);
	wMap2->addToCell((Placeable*)&wChest, 9, 0);
	wMap2->addStop(5, 5, 1);
	wChest.addItem(wDoor.getKey());
	cout << endl << wMap2->toString2() << endl;

}

//wrong map 3, chest on top of exit
void wrongMap3()
{
	Map* wMap3 = new Map("wmap3", 10, 10);
	Chest wChest;
	Door wDoor;
	wMap3->setRowWall(5, 0, 9);
	wMap3->addToCell((Placeable*)&wChest, 9, 9);
	cout << endl << wMap3->toString2() << endl;
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


int main(int argc, char *argv[])
{
	int k;
	
	std::srand(time(0));
	campainCreator();

	//reboot();
	
	//cout << endl << "Aaaaaah yeeeee daaawg!!!!";
	
	//Player myPlayer = Player();
	
	//Game newGame = Game();
	/*
	Player test = Player();
	int *anArray = test.getAllBaseAbl();

	for (int i = 0; i < 6;i++){
		cout << *anArray << " " << endl;
		anArray++;
	}
	*/
	system("pause");
	//cin >> k;
}


