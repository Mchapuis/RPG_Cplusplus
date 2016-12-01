#pragma once

#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "config.h"
#include "Logger.h"

class Subject
{
	//Lets keep a track of all the loggers we have observing
	vector<Logger*> list;

public:
	void Attach(Logger *alogger);
	void Detach(Logger *alogger);
	void Notify(string newlog);
};

#endif _SUBJECT_H_