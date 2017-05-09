#pragma once

#pragma once
#include <string>

class MenuItem {
	bool* _flag;
	std::string _labelIfTrue, _labelIfFalse;

public:
	MenuItem(std::string labelIfTrue, std::string labelIfFalse = "", bool* flag = nullptr)
		: _labelIfTrue(labelIfTrue), _labelIfFalse(labelIfFalse), _flag(flag) {}

	std::string format() {
		if (_flag == nullptr) {
			return _labelIfTrue;
		}
		else
			return *_flag ? _labelIfTrue : _labelIfFalse;
	}
};