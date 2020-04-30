#pragma once
#include <string>

class Colony
{
protected:
	std::string _name;
	int _numberOfIndividuals;
public:
	std::string getName() { return this->_name; }
	int getNumberOfIndividuals() { return this->_numberOfIndividuals; }
	virtual void setNumberOfIndividuals(int value) { }

	Colony(std::string name, int numberOfIndividuals) : _name(name), _numberOfIndividuals(numberOfIndividuals) { }

	virtual void Reproduce() { }
};

