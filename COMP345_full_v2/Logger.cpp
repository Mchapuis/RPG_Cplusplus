#include "stdafx.h"
#include "Logger.h"

Logger::Logger(std::string n)
{
	this->name = n;
}

void Logger::Update(string l)
{
	this->log = l;

	std::ofstream logging;

	logging.open("log.txt", std::ios_base::app);

	logging << "New log at  " << name << " is: " << log << "\n" << std::endl;

	logging.close();

}