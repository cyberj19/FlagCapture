#pragma once
#include <vector>
#include <functional>
#include "AbstractPlayer.h"
class AlgorithmRegistration {
	static std::vector<AbstractPlayer*> algorithms;
	static int currentAlgorithm;
public:
	AlgorithmRegistration(std::string algorithmName,
		std::function<AbstractPlayer*()> generator);
	static AbstractPlayer* nextAlgorithm();
};