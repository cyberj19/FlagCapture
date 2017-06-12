#pragma once
#include <map>
#include<vector>
#include <functional>
#include "AbstractPlayer.h"

class AlgorithmRegistration {
	static std::map < std::string, std::function<AbstractPlayer*()>> _generators;
	static std::vector<std::string> _names;
	static int _current;
public:
	AlgorithmRegistration(std::string algorithmName,
		std::function<AbstractPlayer*()> generator);
	static AbstractPlayer* nextAlgorithm();
};
