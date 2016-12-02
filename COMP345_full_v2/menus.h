#pragma once

#ifndef _MENUS_H_
#define _MENUS_H_

#include "config.h"
#include "map.h"
#include "game.h"
#include "campain.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

void menuMenus();
void characterCreator();
void campainCreator();
void mapCreator();
void mapEditor();
void wrongMaps();
void characterEditor();





#endif