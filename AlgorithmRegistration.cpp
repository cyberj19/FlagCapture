#include "AlgorithmRegistration.h"
using namespace std;
map < string, function<AbstractPlayer*()>> 
		AlgorithmRegistration::_generators;
vector<string> AlgorithmRegistration::_names;
int AlgorithmRegistration::_current = 0;

AlgorithmRegistration::AlgorithmRegistration(std::string algorithmName,
	std::function<AbstractPlayer*()> generator) {
//	_generators[algorithmName] = generator;
//	_names.push_back(algorithmName);
}

AbstractPlayer * AlgorithmRegistration::nextAlgorithm() {
	AbstractPlayer* ret = _generators[_names[_current++]]();
	if (_current == (int)_names.size())
		_current = 0;
	return ret;
}
