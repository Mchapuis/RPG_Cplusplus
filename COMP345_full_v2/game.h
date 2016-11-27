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

	static Game INSTANCE;

	
	Map map;
	Player player;
	
public:
	Game();
	~Game();
	Game getInstance();
	void turn(GameCharacter);
	Player loadPlayer();
	Map loadMap();
	void createPlayer();
	void createPlayerFromLoad();
	void mapEditor(Map map);
	void display();
};

#endif

