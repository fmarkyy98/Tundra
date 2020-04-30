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

	void Hunt(std::vector<PreyColony*> preyColonys)
	{
		srand((int)time(0));
		PreyColony* hunted;
		int i = 0;
		do
		{
			hunted = preyColonys[rand() % preyColonys.size()];
			++i;
		} while (hunted->getNumberOfIndividuals() == 0 && i < 10);
		if (hunted->getNumberOfIndividuals() < hunted->DieingRate(this->_numberOfIndividuals)) // Dieing rate returns an integer that represents the amount of dead members after an atack.
		{
			hunted->setNumberOfIndividuals(0);
			std::cout << hunted->getName() << " Kipusztult!!!" << std::endl;
			(this->_numberOfIndividuals *= 3) /= 4;
			if (this->_numberOfIndividuals < 2)
			{
				std::cout << this->_name << "Éhanhalt :'(" << std::endl;
			}
		}
		else
		{
			hunted->Die(this->_numberOfIndividuals); // Die reduces the (numberOfIndividuals) by (DyeingRate * parameter)
		}
	}
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

