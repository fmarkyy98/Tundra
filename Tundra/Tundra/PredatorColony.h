#pragma once
#include <vector>
#include <ctime>
#include <iostream>
#include "Colony.h"
#include "PreyColony.h"

class PredatorColony : public Colony
{
public:
	PredatorColony(std::string name, int numberOfIndividuals) : Colony(name, numberOfIndividuals) { }
	void Hunt(std::vector<PreyColony*> preyColonys);
};

class SnowyOwlColony : public PredatorColony
{
public:
	SnowyOwlColony(std::string name, int numberOfIndividuals) : PredatorColony(name, numberOfIndividuals) { }

	void Reproduce() override
	{
		this->_numberOfIndividuals += (this->_numberOfIndividuals / 4);
	}
};

class PolarFoxColony : public PredatorColony
{
public:
	PolarFoxColony(std::string name, int numberOfIndividuals) : PredatorColony(name, numberOfIndividuals) { }

	void Reproduce() override
	{
		this->_numberOfIndividuals += ((this->_numberOfIndividuals * 3) / 4);
	}

};

class WolfColony : public PredatorColony
{
public:
	WolfColony(std::string name, int numberOfIndividuals) : PredatorColony(name, numberOfIndividuals) { }

	void Reproduce() override
	{
		this->_numberOfIndividuals += ((this->_numberOfIndividuals * 2) / 4);
	}
};

