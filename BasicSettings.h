#pragma once
#include<string>
#include <vector>
#include <map>
#include "enums.h"

class BasicSettings {
	std::vector<std::string> errors;

	BoardOptions _boardOptions;  //enum: F, R
	InputOptions _inputOptions;  //enum: F, K
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
	InputOptions getInputOptions() const { 
		return _boardOptions == BoardOptions::Randomized ? 
			InputOptions::Keyboard : _inputOptions; 
	}
	std::string getPath() const { return _path; }
	bool hasErrors() const { return !errors.empty(); }
	void showErrors() const;
	int getDelay() const { return isQuiet() ? 0 : _delay; }
	bool isQuiet() const { return _quiet && _inputOptions == InputOptions::FromFile;}
private:
	std::map<std::string, std::string> generateCommandMap(int argc, char* argv[]);
	void parsePathArgument(const std::string& value);
	void parseDelayArgument(const std::string& value);
	void parseBoardArgument(const std::string& value);
	void parseMovesArgument(const std::string& value);

	void noValueError(std::string param);
	void duplicateValueError(std::string param);
	void illegalValueError(std::string param, std::string value);
	void unknownParamError(std::string param);
	void argWithoutParamError(std::string value);
};