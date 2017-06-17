#include "BasicSettings.h"
#include <iostream>
#include "Utils.h"
using namespace std;

BasicSettings::BasicSettings(const BasicSettings& s) : 
	_boardOptions(s._boardOptions), _numRounds(s._numRounds),
	_inputOptionsA(s._inputOptionsA), _inputOptionsB(s._inputOptionsB),
	_path(s._path), _quiet(s._quiet), _delay(s._delay)
{}

bool isKnownParam(string param) {
	return	param == "-path" ||
			param == "-quiet" ||
			param == "-board" ||
			param == "-delay" ||
			param == "-moves";
}

bool isParam(string str) {
	return str[0] == '-';
}
map<string, string> BasicSettings::generateCommandMap(int argc, char* argv[]) {
	map<string, string> commandMap = map<string, string>();


	for (int i = 1; i < argc;) {
		string param(""), value("");
		param = argv[i++];

		if (!isParam(param))
			throw "Not a param name: " + param;
		if (!isKnownParam(param))
			throw "Unknown param: " + param;
		if (commandMap.find(param) != commandMap.end())
			throw "Duplicate param: " + param;
		for (; i < argc && !isParam(argv[i]); i++) {
			value += argv[i];
			value += ',';
		}
		if (value.length() > 0)
			value.pop_back();
		commandMap[param] = value;
	}
	return commandMap;
}

BasicSettings::BasicSettings(int argc, char * argv[]) {
	map<string, string> commandMap = generateCommandMap(argc, argv);
	auto none = commandMap.end();

	if (commandMap.find("-path") != none)
		parsePathArgument(commandMap["-path"]);
	else
		_path = string("");

	if (commandMap.find("-quiet") != none)
		parseQuietArgument(commandMap["-quiet"]);
	else
		_quiet = false;

	if (commandMap.find("-delay") != none)
		parseDelayArgument(commandMap["-delay"]);
	else
		_delay = 20;

	if (commandMap.find("-board") != none)
		parseBoardArgument(commandMap["-board"]);
	else {
		_boardOptions = BoardOptions::Randomized;
		_numRounds = 10;
	}

	if (commandMap.find("-moves") != none)
		parseInputArgument(commandMap["-moves"]);
	else {
		_inputOptionsA = InputOptions::Algorithm;
		_inputOptionsB = InputOptions::Algorithm;
	}
}
BoardOptions parseBoardOption(const std::string& opt) {
	if (opt == "f") return BoardOptions::FromFile;
	if (opt == "r") return BoardOptions::Randomized;
	throw "Illegal board option " + opt;
}
void BasicSettings::parseBoardArgument(const std::string& value) {
	vector<string> values = verifyNumOptions("board", value, 1, 2);
	_boardOptions = parseBoardOption(values[0]);
	if (values.size() == 2)
		_numRounds = stoi(values[1]);
}

InputOptions parseInputOption(const char opt) {
	if (opt == 'f') return InputOptions::FromFile;
	if (opt == 'k') return InputOptions::Keyboard;
	if (opt == 'a') return InputOptions::Algorithm;
	throw "Unknown input option " + opt;
}

void BasicSettings::parseInputArgument(const std::string& value) {
	verifyNumOptions("moves", value);
	char first, second;
	if (value.length() == 1) {
		first = second = value[0];
	}
	else if (value.length() == 2) {
		first = value[0];
		second = value[1];
	}
	else throw "Moves option cannot have more than 3 charactes";

	_inputOptionsA = parseInputOption(first);
	_inputOptionsB = parseInputOption(second);
}

void BasicSettings::parseQuietArgument(const std::string & value)
{
	verifyNumOptions("quiet", value, 0, 0);
	_quiet = true;
}

void BasicSettings::parsePathArgument(const std::string& value) {
	verifyNumOptions("path", value);
	_path = value;

	// strip "
	if (_path.front() == '\"' || _path.back() == '\"') {
		if (_path.back() != _path.front())
			throw "Illegal value for path argument: " + value;
		else {
			_path.pop_back();
			_path.erase(0, 1);
		}
	}
	if (_path.back() == '\\')
		_path.pop_back();
}

void BasicSettings::parseDelayArgument(const std::string& value) {
	verifyNumOptions("delay", value);
	_delay = stoi(value);
}

vector<string> verifyNumOptions(const std::string& argName, 
	const std::string& value, 
	int minOptions, int maxOptions) {

	if (minOptions > 0 && value == "")
		throw "No value was passed to " + argName + " argument";
	if (minOptions == 0 && maxOptions == 0 && value != "")
		throw "Too many options were passed to " + argName + " argument";
	vector<string> values = split(value, ",");
	if (values.size() < minOptions)
		throw "Not enough options were passed to " + argName + " argument";
	else if (values.size() > maxOptions)
		throw "Too many options were passed to " + argName + " argument";
	return values;
}