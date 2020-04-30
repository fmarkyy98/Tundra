#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include "PreyColony.h"
#include "PredatorColony.h"

using namespace std;

vector<PreyColony*> preyColonys;
vector<PredatorColony*> predatorColonys;
int BasePredatorPopulation;

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

void read(string filename)
{
	fstream fs;
	fs.open(filename);
	if (fs.fail())
	{
		return;
	}
	int preys, predators;
	fs >> preys >> predators;
	cout << preys << " " << predators << endl;



	for (int i = 0; i < preys; ++i)
	{
		string name;
		char c;
		int population;
		PreyColony* tmp;
		fs >> name >> c >> population;
		cout << name << " " << c << " " << population << endl;
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

	BasePredatorPopulation = 0;

	for (int i = 0; i < predators; ++i)
	{
		string name;
		char c;
		int population;
		PredatorColony* tmp;
		fs >> name >> c >> population;
		cout << name << " " << c << " " << population << endl;
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
}

void simulate()
{
	for (unsigned long long i = 1; 0 < GetPreyPopulation(preyColonys) && GetPredatorPopulation(predatorColonys) < BasePredatorPopulation * 4; ++i)
	{
		cout << "\n-------------------Day " << i << "----------------------" << endl << endl;
		for (PredatorColony* item : predatorColonys)
		{
			if (1 < item->getNumberOfIndividuals());
			{
				cout << item->getName() << " nevû ragadozó populáció vadászni indult!" << endl;
				item->Hunt(preyColonys);
			}
		}
		if (i % 2 == 0)
		{
			for (PreyColony* item : preyColonys)
			{
				if (typeid(*item) == typeid(LemmingColony) || typeid(*item) == typeid(PolarRabbitColony))
				{
					if (1 < item->getNumberOfIndividuals())
					{
						item->Reproduce();
						cout << item->getName() << " kolónia Szaporodott, új egyedszámuk: " << item->getNumberOfIndividuals() << endl;
					}
				}
			}
		}
		if (i % 4 == 0)
		{
			for (PredatorColony* item : predatorColonys)
			{
				if (typeid(*item) == typeid(GroundSquirrelColony))
				{
					if (1 < item->getNumberOfIndividuals());
					{
						item->Reproduce();
						cout << item->getName() << " kolónia Szaporodott, új egyedszámuk: " << item->getNumberOfIndividuals() << endl;
					}
				}
			}
		}
		if (i % 8 == 0)
		{
			for (PredatorColony* item : predatorColonys)
			{
				if (1 < item->getNumberOfIndividuals());
				{
					item->Reproduce();
					cout << item->getName() << " kolónia Szaporodott, új egyedszámuk: " << item->getNumberOfIndividuals() << endl;
				}
			}
		}
	}
}

//#define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
	string filename;
	cin >> filename;
	read(filename);

	simulate();

	return 0;
}

#else

#define CATCH_CONFIG_MAIN

#include "./Test/src/catch.hpp"

TEST_CASE("00")
{
	read("./Test/00.txt");
	CHECK(preyColonys.size() == 4);
	CHECK(predatorColonys.size() == 2);
	CHECK(preyColonys[0]->getName() == "kicsik");
	CHECK(preyColonys[0]->getNumberOfIndividuals() == 86);
	CHECK(preyColonys[1]->getName() == "picik");
	CHECK(preyColonys[1]->getNumberOfIndividuals() == 90);
	CHECK(preyColonys[2]->getName() == "szaporak");
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 26);
	CHECK(preyColonys[3]->getName() == "szorgosak");
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 12);
	CHECK(predatorColonys[0]->getName() == "ehesek");
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 12);
	CHECK(predatorColonys[1]->getName() == "tollasak");
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 6);

	for (Colony* item : preyColonys)
	{
		item->Reproduce();
	}
	for (Colony* item : predatorColonys)
	{
		item->Reproduce();
	}

	CHECK(preyColonys[0]->getNumberOfIndividuals() == 172);
	CHECK(preyColonys[1]->getNumberOfIndividuals() == 180);
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 39);
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 24);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 18);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 7);

	for (int i = 0; i < 2; i++)
	{
		vector<PreyColony*> testVec;
		testVec.push_back(preyColonys[i]);
		predatorColonys[i]->Hunt(testVec);
	}

	CHECK(preyColonys[0]->getNumberOfIndividuals() == 100);
	CHECK(preyColonys[1]->getNumberOfIndividuals() == 152);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 18);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 7);

	for (int i = 0; i < 2; i++)
	{
		vector<PreyColony*> testVec;
		testVec.push_back(preyColonys[i + 2]);
		predatorColonys[i]->Hunt(testVec);
	}

	CHECK(preyColonys[2]->getNumberOfIndividuals() == 3);
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 10);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 18);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 7);

	for (int i = 0; i < 2; i++)
	{
		vector<PreyColony*> testVec;
		testVec.push_back(preyColonys[i + 2]);
		predatorColonys[i]->Hunt(testVec);
	}

	CHECK(preyColonys[2]->getNumberOfIndividuals() == 0);
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 0);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 13);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 5);
}

TEST_CASE("01")
{
	for (int i = 0; i < 4; i++)
	{
		preyColonys.pop_back();
	}
	for (int i = 0; i < 2; i++)
	{
		predatorColonys.pop_back();
	}
	read("./Test/01.txt");
	CHECK(preyColonys.size() == 4);
	CHECK(predatorColonys.size() == 3);
	CHECK(preyColonys[0]->getName() == "fogyik");
	CHECK(preyColonys[0]->getNumberOfIndividuals() == 15);
	CHECK(preyColonys[1]->getName() == "izek");
	CHECK(preyColonys[1]->getNumberOfIndividuals() == 39);
	CHECK(preyColonys[2]->getName() == "vackok");
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 23);
	CHECK(preyColonys[3]->getName() == "cukik");
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 52);
	CHECK(predatorColonys[0]->getName() == "szomjasak");
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 12);
	CHECK(predatorColonys[1]->getName() == "vukkok");
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 7);

	for (Colony* item : preyColonys)
	{
		item->Reproduce();
	}
	for (Colony* item : predatorColonys)
	{
		item->Reproduce();
	}

	CHECK(preyColonys[0]->getNumberOfIndividuals() == 22);
	CHECK(preyColonys[1]->getNumberOfIndividuals() == 78);
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 34);
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 104);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 18);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 12);

	for (int i = 0; i < 3; i++)
	{
		vector<PreyColony*> testVec;
		testVec.push_back(preyColonys[i]);
		predatorColonys[i]->Hunt(testVec);
	}

	CHECK(preyColonys[0]->getNumberOfIndividuals() == 0);
	CHECK(preyColonys[1]->getNumberOfIndividuals() == 30);
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 20);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 13);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 12);
	CHECK(predatorColonys[2]->getNumberOfIndividuals() == 7);

	for (int i = 0; i < 3; i++)
	{
		vector<PreyColony*> testVec;
		testVec.push_back(preyColonys[i + 1]);
		predatorColonys[i]->Hunt(testVec);
	}

	CHECK(preyColonys[1]->getNumberOfIndividuals() == 0);
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 0);
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 90);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 9);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 9);
	CHECK(predatorColonys[2]->getNumberOfIndividuals() == 7);

	for (int i = 0; i < 3; i++)
	{
		vector<PreyColony*> testVec;
		testVec.push_back(preyColonys[i + 1]);
		predatorColonys[i]->Hunt(testVec);
	}

	CHECK(preyColonys[1]->getNumberOfIndividuals() == 0);
	CHECK(preyColonys[2]->getNumberOfIndividuals() == 0);
	CHECK(preyColonys[3]->getNumberOfIndividuals() == 76);
	CHECK(predatorColonys[0]->getNumberOfIndividuals() == 6);
	CHECK(predatorColonys[1]->getNumberOfIndividuals() == 6);
	CHECK(predatorColonys[2]->getNumberOfIndividuals() == 7);
}

TEST_CASE("WhiteBox")
{
	SnowyOwlColony soc("t03",0);
	PolarFoxColony pfc("t03", 0);
	WolfColony wc("t03", 0);
	LemmingColony lc("t03", 0);
	PolarRabbitColony prc("t03", 0);
	GroundSquirrelColony gsc("t03", 0);

	soc.setNumberOfIndividuals(1000);
	pfc.setNumberOfIndividuals(1000);
	wc.setNumberOfIndividuals(1000);
	lc.setNumberOfIndividuals(1000);
	prc.setNumberOfIndividuals(1000);
	gsc.setNumberOfIndividuals(1000);

	CHECK(soc.getNumberOfIndividuals() == 0);
	CHECK(pfc.getNumberOfIndividuals() == 0);
	CHECK(wc.getNumberOfIndividuals() == 0);
	CHECK(lc.getNumberOfIndividuals() == 30);
	CHECK(prc.getNumberOfIndividuals() == 20);
	CHECK(gsc.getNumberOfIndividuals() == 40);
}

#endif
