#include "BasicSettings.h"
#include <iostream>
using namespace std;

BasicSettings::BasicSettings(const BasicSettings& s) : 
	_boardOptions(s._boardOptions), _inputOptions(s._inputOptions),
	_path(s._path), _quiet(s._quiet), _delay(s._delay)
{}


void BasicSettings::showErrors() const{
	for (const string& error : errors)
		cout << error << endl;
}

map<string, string> BasicSettings::generateCommandMap(int argc, char* argv[]) {
	map<string, string> commandMap = map<string, string>();

	for (int i = 1; i < argc;) {
		string param(""), value("");
		param = argv[i++];

		if (param[0] != '-') {
			argWithoutParamError(param);
			break;
		}

		if (param != "-path" && param != "-quiet" && param != "-board" &&
			param != "-delay" && param != "-moves") {
			unknownParamError(param);
			break;
		}

		if (commandMap.find(param) != commandMap.end()) {
			duplicateValueError(param);
			break;
		}

		if (i == argc && param != "-quiet") {
			noValueError(param);
			break;
		}

		// value after -quiet is illegal
		if (param == "-quiet" && 
			i < argc && argv[i][0] != '-') {
			illegalValueError("-quiet", argv[i]);
			break;
		}

		value = param == "-quiet" ? "" : argv[i++];
		//param after param
		if (value[0] == '-') {
			noValueError(param);
			break;
		}

		commandMap[param] = value;
	}
	return commandMap;
}

BasicSettings::BasicSettings(int argc, char * argv[]){
	map<string, string> commandMap = generateCommandMap(argc, argv);
	if (!errors.empty()) return;

	auto none = commandMap.end();

	if (commandMap.find("-path") != none)
		parsePathArgument(commandMap["-path"]);
	else
		_path = string("");
	
	if (commandMap.find("-quiet") != none)
		_quiet = true;
	else
		_quiet = false;

	if (commandMap.find("-delay") != none)
		parseDelayArgument(commandMap["-delay"]);
	else
		_delay = 20;

	if (commandMap.find("-board") != none)
		parseBoardArgument(commandMap["-board"]);
	else
		_boardOptions = BoardOptions::Randomized;

	if (commandMap.find("-moves") != none)
		parseMovesArgument(commandMap["-moves"]);
	else
		_inputOptions = InputOptions::Keyboard;
}


void BasicSettings::parseBoardArgument(const std::string& value) {
	if (value == "f")
		_boardOptions = BoardOptions::FromFile;
	else if (value == "r")
		_boardOptions = BoardOptions::Randomized;
	else
		illegalValueError("Board", value);
}

void BasicSettings::parseMovesArgument(const std::string& value) {
	if (value == "f")
		_inputOptions = InputOptions::FromFile;
	else if (value == "k")
		_inputOptions = InputOptions::Keyboard;
	else
		illegalValueError("Moves", value);
}

void BasicSettings::parsePathArgument(const std::string& value) {
	_path = value;

	// strip "
	if (_path.front() == '\"' || _path.back() == '\"') {
		if (_path.back() != _path.front())
			illegalValueError("Path", _path);
		else {
			_path.pop_back();
			_path.erase(0, 1);
		}
	}
	if (_path.back() == '\\')
		_path.pop_back();
}

void BasicSettings::parseDelayArgument(const std::string& value) {
	_delay = atoi(value.c_str());
}

void BasicSettings::noValueError(string param) {
	errors.push_back(param + " parameter was declared but supplied no value");
}

void BasicSettings::duplicateValueError(string param) {
	errors.push_back(param + " parameter was supplied with duplicate values");
}

void BasicSettings::illegalValueError(string param, string value) {
	errors.push_back(param + " was supplied an illegal value \'" + value + "\'");
}

void BasicSettings::unknownParamError(string param) {
	errors.push_back("Unknown parameter with name " + param);
}

void BasicSettings::argWithoutParamError(std::string value) {
	errors.push_back("Argument " + value + " was supplied without a param name");
}