#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "cell.h"
#include <map>


using namespace std;


/*bool ifCharValid(char ch) {

	static int A_TOOL[3] = { 0 };
	static int B_TOOL[3] = { 0 };

	static char A_TOOL = 0;
	static char B_TOOL = 0;

	static char S_SHOWS = 0;
	static char T_SHOWS = 0;

	static char WRONG_CHAR = { 0 };

	if (ch == '1' || ch == '2' || ch == '3') {
		A_TOOL[ch - '1']++;
	}
	else if (ch == '7' || ch == '8' || ch == '9') {
		B_TOOL[ch - '7']++;
	}
	else if (ch == 'S') {
		S_SHOWS = 1;
	}
	else if (ch == 'T') {
		T_SHOWS = 1;
	}
	else {
		WRONG_CHAR++;
	}
	
}*/

bool updateBoard(char **board, string str) {
	// we need to read only 13 characters from str

	static int i = 0;
	int j = 0;

	for (auto k : str) {
		if (ifCharValid(k)) {

		}
		if (j < COLS) {
			board[i][j++] = k;
		}
	}
	i++;
}

void boardInitialize(char **board) {

	for (int i = 0; i < ROWS; i++) {
		board[i] = new char[COLS];
		for (int j = 0; j < COLS; j++) {
			board[i][j] = ' ';
		}
	}
}


string readLineFromTextFile(ifstream file) {
	//we need to read line from file text until '\r\n'  || '\n' 

	string str;
	char ch, tempCh = ' ';


	file.get(ch);
	while (ch != EOF) {
		//if temp = '\r' & ch = '\n'  :: we don't want that '\r' will be on the string
		if (tempCh == '\r' && ch == '\n') {  //end of line
			str.erase(str.end() - 1);
			return str;
		}
		//if temp = '\r' & ch != '\n' :: when we check the board - we will print an ERROR
		else if (ch == '\n') {
			return str;
		}
		str += ch;
		tempCh = ch;
		file.get(ch);
	}
	return str;
}



char **getBoardFromFile(const string fileName) {
	//we need to check whether each file is valid
	char **board;
	boardInitialize(board);

	vector<string> errorMsgs;  //msg.size() == 0

	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "error opening file " << fileName << endl;
		return nullptr; //?
	}

	int counter = 0;
	bool ifNotFinish = true;

	string line = readLineFromTextFile(file);
	while (!file.eof() && ifNotFinish) {
		counter++;
		if (counter <= ROWS) {
			if (!updateBoard(board, line)) {

			}
			line = readLineFromTextFile(file);
		}
		else {
			ifNotFinish = false;
		}
	}

	file.close();

	if (!errorMsgs.size()) {  //if errors was found
		for (auto i : errorMsgs) {
			cout << i << endl;
		}
		return nullptr;
	}

	return board;
}



