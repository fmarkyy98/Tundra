#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include "PreyColony.h"
#include "PredatorColony.h"

using namespace std;

int GetPreyPopulation(vector<PreyColony*> preyColonys)
{
	int result = 0;
	for (PreyColony* item : preyColonys)
	{
		result += item->getNumberOfIndividuals();
	}
	return result;
}

int GetPredatorPopulation(vector<PredatorColony*> predatorColonys)
{
	int result = 0;
	for (PredatorColony* item : predatorColonys)
	{
		result += item->getNumberOfIndividuals();
	}
	return result;
}

int main()
{
	string filename;
	cin >> filename;
	fstream fs;
	fs.open(filename);
	int preys, predators;
	fs >> preys >> predators;

	vector<PreyColony*> preyColonys;
	vector<PredatorColony*> predatorColonys;

	for (int i = 0; i < preys; ++i)
	{
		string name;
		char c;
		int population;
		PreyColony* tmp;
		fs >> name >> c >> population;
		switch (c)
		{
		case 'l':
			tmp = new LemmingColony(name, population);
			break;
		case 'n':
			tmp = new PolarRabbitColony(name, population);
			break;
		case 'u':
			tmp = new GroundSquirrelColony(name, population);
			break;
		}
		preyColonys.push_back(tmp);
	}

	int BasePredatorPopulation = 0;

	for (int i = 0; i < predators; ++i)
	{
		string name;
		char c;
		int population;
		PredatorColony* tmp;
		fs >> name >> c >> population;
		BasePredatorPopulation += population;
		switch (c)
		{
		case 'h':
			tmp = new SnowyOwlColony(name, population);
			break;
		case 's':
			tmp = new PolarFoxColony(name, population);
			break;
		case 'f':
			tmp = new WolfColony(name, population);
			break;
		}
		predatorColonys.push_back(tmp);
	}

	for (unsigned long long i = 1; 0 < GetPreyPopulation(preyColonys) && GetPredatorPopulation(predatorColonys) < BasePredatorPopulation * 4; ++i)
	{
		for (PredatorColony* item : predatorColonys)
		{
			item->Hunt(preyColonys);
			cout << item->getName() << " nevû ragadozó populáció vadászni indult!" << endl;
		}
		if (i % 2 == 0)
		{
			for (PreyColony* item : preyColonys)
			{
				if (typeid(*item) == typeid(LemmingColony) || typeid(*item) == typeid(PolarRabbitColony))
				{
					item->Reproduce();
					cout << item->getName() << " kolónia Szaporodott, új egyedszámuk: " << item->getNumberOfIndividuals() << endl;
				}
			}
		}
		if (i % 4 == 0)
		{
			for (PredatorColony* item : predatorColonys)
			{
				if (typeid(*item) == typeid(GroundSquirrelColony))
				{
					item->Reproduce();
					cout << item->getName() << " kolónia Szaporodott, új egyedszámuk: " << item->getNumberOfIndividuals() << endl;
				}
			}
		}
		if (i % 8 == 0)
		{
			for (PredatorColony* item : predatorColonys)
			{
				item->Reproduce();
				cout << item->getName() << " kolónia Szaporodott, új egyedszámuk: " << item->getNumberOfIndividuals() << endl;
			}
		}
	}

	cout << "Hello World!\n";
	return 0;
}
