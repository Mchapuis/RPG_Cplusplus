#pragma once

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include "config.h"
#include "Observer.h"

class Logger : Observer
{
	//Name of the logger
	//create variables to use on updates
	string name;
	string log;

public:
	Logger(std::string n);
	void Update(string log);

};

#endif _LOGGER_H_