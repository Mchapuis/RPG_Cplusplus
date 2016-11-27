
#ifndef _INVENTORY_EXCEPTIONS_H_
#define _INVENTORY_EXCEPTIONS_H_

#pragma once

#include "config.h"
#include <exception>


class IllegalEnchantmentException : public exception
{
	std::string err_msg;

public:
	IllegalEnchantmentException(const std::string itemName, const std::string typeName, const std::string enchantmentName)
		: err_msg(std::string("Item \"" + itemName + "\" of type " + typeName + " cannot receive " +enchantmentName + " enchantment"))
	{}

	virtual const char* what() const throw()
	{
		return err_msg.c_str();
	}
};


class EmptyTypeException : public exception
{
	std::string err_msg;

public:
	EmptyTypeException(const std::string className)
		: err_msg(std::string("No item type specified for: " + className))
	{}

	virtual const char* what() const throw()
	{
		return err_msg.c_str();
	}
};

/*
class ItemNotFoundException : public exception
{
	std::string err_msg;

public:
	ItemNotFoundException(const std::string itemName, const std::string emplacement)
		: err_msg(std::string("Item \"" + itemName + "\" cannot be found in " + emplacement))
	{}

	virtual const char* what() const throw()
	{
		return err_msg.c_str();
	}
};

class ItemDuplicateException : public exception
{
	std::string err_msg;

public:
	ItemDuplicateException(const std::string itemName, const std::string emplacement)
		: err_msg(std::string("Item \"" + itemName + "\" already in " + emplacement))
	{}

	virtual const char* what() const throw()
	{
		return err_msg.c_str();
	}
};
*/

#endif