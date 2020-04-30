#pragma once
#include "Colony.h"

class PreyColony : public Colony
{
public:
	PreyColony(std::string name, int numberOfIndividuals) : Colony(name, numberOfIndividuals) { }

	virtual int DieingRate(int predatorCount)
	{
		int result = predatorCount * 2;
		return result;
	}
	
	void Die(int predatorCount)
	{
		this->_numberOfIndividuals -= DieingRate(predatorCount);
	}

	void Reproduce() override
	{
		this->setNumberOfIndividuals(this->_numberOfIndividuals * 2);
	}
};

class LemmingColony : public PreyColony
{
public:
	LemmingColony(std::string name, int numberOfIndividuals) : PreyColony(name, numberOfIndividuals) { }

	void setNumberOfIndividuals(int value) override
	{
		this->_numberOfIndividuals = value < 200 ? value : 30;
	}

	virtual int DieingRate(int predatorCount) override
	{
		int result = predatorCount * 4;
		return result;
	}
};

class PolarRabbitColony : public PreyColony
{
public:
	PolarRabbitColony(std::string name, int numberOfIndividuals) : PreyColony(name, numberOfIndividuals) { }

	void setNumberOfIndividuals(int value) override
	{
		this->_numberOfIndividuals = value < 100 ? value : 20;
	}

	virtual void Reproduce() override
	{
		this->setNumberOfIndividuals((int)(this->_numberOfIndividuals * 1.5));
	}
};

class GroundSquirrelColony : public PreyColony
{
public:
	GroundSquirrelColony(std::string name, int numberOfIndividuals) : PreyColony(name, numberOfIndividuals) { }

	void setNumberOfIndividuals(int value) override
	{
		this->_numberOfIndividuals = value < 200 ? value : 40;
	}
};