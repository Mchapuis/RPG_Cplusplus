#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "config.h"
#include "campain.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

//!Game class that will control the whole game
class Game: public Subject
{
private:
	Campain* campain;
	Map* map;
	vector<vector<Cell*>> board;
	Player* player;
	Cell* pCell;
	std::list<GameCharacter*> characters;
	std::map<Placeable*, Cell*> objects;

	static bool isCharacter(Placeable* obj);//
	void Game::removePos(Placeable* obj);//
	void cleanUp();
	void play();//
	bool nextTurn();//
	bool setupMap(Map* aMap);
public:
	
	//this constructor is calling a Campain 
	Game() :
		campain(nullptr), player(nullptr),
		characters(std::list<GameCharacter*>()),
		objects(std::map<Placeable*, Cell*>()) {}
	/*
	//this constructor is calling a map only
	Game() :
		map(nullptr), player(nullptr),
		characters(std::list<GameCharacter*>()),
		objects(std::map<Placeable*, Cell*>()) {}
*/
	~Game() {}
	Game getInstance();
	bool startGame(Map* aMap, Player* aPlayer);//this is the old version of start game
	bool startGame(Campain* aCampain, Player* aPlayer);//New version of start game
	
	Player loadPlayer();
	Map loadMap();
	
	void startGame();

	void createPlayer();
	void createPlayerFromLoad();
	void mapEditor(Map map);
	void display(GameCharacter *gh);
};

#endif

