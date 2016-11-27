#include "config.h"

#include <string>
#include <boost\archive\text_iarchive.hpp>
#include <boost\archive\text_oarchive.hpp>
#include <boost\serialization\export.hpp>

class MySerializable
{
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{}

public:
	virtual ~MySerializable(){}
	virtual void save(std::string filename) = 0;
	virtual void load(std::string filename) = 0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(MySerializable);