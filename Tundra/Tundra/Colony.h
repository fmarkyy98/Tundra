#pragma once
#include <string>

class Colony
{
protected:
	std::string _name;
	int _numberOfIndividuals;
public:
	std::string getName()
	{
		std::string result = this->_name;
		return result;
	}
	int getNumberOfIndividuals()
	{
		int result = this->_numberOfIndividuals;
		return result;
	}
	virtual void setNumberOfIndividuals(int value) { }

	Colony(std::string name, int numberOfIndividuals) : _name(name), _numberOfIndividuals(numberOfIndividuals) { }

	virtual void Reproduce() { }
};

