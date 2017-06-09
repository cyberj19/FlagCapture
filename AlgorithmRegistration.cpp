#include "AlgorithmRegistration.h"
using namespace std;

vector<AbstractPlayer*> AlgorithmRegistration::algorithms =
	vector<AbstractPlayer*>();

int AlgorithmRegistration::currentAlgorithm = 0;


AlgorithmRegistration::AlgorithmRegistration(std::string algorithmName,
	std::function<AbstractPlayer*()> generator)
{
	algorithms.push_back(generator());
}

AbstractPlayer * AlgorithmRegistration::nextAlgorithm()
{
	return algorithms[currentAlgorithm++];
	if (currentAlgorithm == algorithms.size())
		currentAlgorithm = 0;
}
