
#pragma once

#ifndef _PLACEABLE_H_
#define _PLACEABLE_H_

#include "config.h"

#include "serializable.h"

#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

class Placeable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{}

protected:
	Placeable(){}

public:
	virtual ~Placeable() {}
	virtual bool isWalkable() = 0;
	virtual std::string getClassName() { return typeid(*this).name(); }
	virtual const std::string getSymbol() = 0;
	virtual void updateLvl(int aLevel) = 0;
	virtual bool reset() = 0;

	/*
	virtual ~Placeable() {}
	virtual bool isWalkable() { return false; }
	virtual std::string getClassName() { return typeid(*this).name(); }
	virtual const std::string getSymbol() { return "?";  }
	virtual void updateLvl(int aLevel){}
	virtual bool reset() { return false; }
	*/
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Placeable);

#endif _PLACEABLE_H_