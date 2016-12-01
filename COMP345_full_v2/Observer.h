#pragma once

#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "config.h"


class Observer
{
public:
	virtual void Update(string l) = 0;
};

#endif _OBSERVER_H_