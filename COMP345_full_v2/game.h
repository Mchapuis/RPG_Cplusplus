#pragma once

#ifndef _GAME_H_
#define _GAME_H_

#include "config.h"
#include "map.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

class Game
{
private:
	
	Map* map;
	vector<vector<Cell*>> board;
	Player* player;
	Cell* pCell;
	std::list<GameCharacter*> characters;
	std::map<Placeable*, Cell*> objects;

	static bool isCharacter(Placeable* obj);//
	void Game::removePos(Placeable* obj);//
	void cleanUp();//
	void play();//
	bool nextTurn();//
public:
	Game() :
		map(nullptr), player(nullptr),
		characters(std::list<GameCharacter*>()),
		objects(std::map<Placeable*, Cell*>()) {}
	~Game() {}
	Game getInstance();
	bool startGame(Map* aMap, Player* aPlayer);//Campain should check map...

	
	Player loadPlayer();
	Map loadMap();
	

	void startGame();

	void createPlayer();
	void createPlayerFromLoad();
	void mapEditor(Map map);
	void display(GameCharacter *gh);
};

#endif

