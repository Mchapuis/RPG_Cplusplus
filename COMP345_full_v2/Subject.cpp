#include "stdafx.h"
#include "Subject.h"


void Subject::Attach(Logger *Logging)
{
	list.push_back(Logging);
}

void Subject::Detach(Logger *Logging)
{
	list.erase(std::remove(list.begin(), list.end(), Logging), list.end());
}

void Subject::NotifyGame(string newlog)
{
	for (vector<Logger*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Update(newlog);
		}
	}
}

void Subject::NotifyMap(string newlog)
{
	for (vector<Logger*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Update(newlog);
		}
	}
}

void Subject::NotifyCharacter(string newlog)
{
	for (vector<Logger*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Update(newlog);
		}
	}
}

void Subject::NotifyDice(string newlog)
{
	for (vector<Logger*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->Update(newlog);
		}
	}
}