#include "PredatorColony.h"

void PredatorColony::Hunt(std::vector<PreyColony*> preyColonys)
{
	srand((int)time(0));
	PreyColony* hunted;
	int i = 0;
	do
	{
		hunted = preyColonys[rand() % preyColonys.size()];
		++i;
	} while (hunted->getNumberOfIndividuals() == 0 && i < 10);
	if (hunted->getNumberOfIndividuals() < hunted->DieingRate(this->_numberOfIndividuals))
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
		hunted->Die(this->_numberOfIndividuals);
	}
}