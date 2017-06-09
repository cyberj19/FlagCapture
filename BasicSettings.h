#pragma once
#include<string>
#include <vector>
#include <map>
#include "enums.h"

std::vector<std::string> verifyNumOptions
	(const std::string& argName, const std::string& value,
		int minOptions = 1, int maxOptions = 1);
class BasicSettings {
	std::vector<std::string> errors;

	BoardOptions _boardOptions;  //enum: F, R
	int _numRounds;

	InputOptions _inputOptionsA;
	InputOptions _inputOptionsB;

	std::string _path;
	bool _quiet;
	int _delay;
public:
	BasicSettings() {}
	BasicSettings(const BasicSettings& s);
	BasicSettings(int argc, char *argv[]);

	BasicSettings& operator = (const BasicSettings& s) {
		*this = BasicSettings(s);
		return *this;
	}

	BoardOptions getBoardOptions() const { return _boardOptions; }
	int getNumRounds() const { return _numRounds; }
	InputOptions getInputOptionsA() const { return _inputOptionsA; }
	InputOptions getInputOptionsB() const { return _inputOptionsB; }

	std::string getPath() const { return _path; }
	bool hasErrors() const { return !errors.empty(); }
	int getDelay() const { return isQuiet() ? 0 : _delay; }
	bool isQuiet() const {
		return _quiet &&
			_inputOptionsA != InputOptions::Keyboard && _inputOptionsB != InputOptions::Keyboard;
	}
private:
	std::map<std::string, std::string> generateCommandMap(int argc, char* argv[]);
	void parsePathArgument(const std::string& value);
	void parseDelayArgument(const std::string& value);
	void parseBoardArgument(const std::string& value);
	void parseInputArgument(const std::string& value);
	void parseQuietArgument(const std::string& value);
};