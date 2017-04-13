#include <iostream>
using namespace std;

void kishkashta(char* name, int num = 10) {

	if (!name) {
		for (int i = 0; i < num; i++) {
			cout << "Mor" << endl;
		}
	}
	else {
		for (int i = 0; i < num; i++) {
			cout << name << endl;
		}
	}
}
void kishkashta(int num = 3) {

	char name[50];
	cout << "pls enter name: ";
	cin >> name;

	for (int i = 0; i < num; i++) {
		cout << name << endl;
	}
}


void swap(int &a, int &b) {  //change byRef
	int temp = a;
	a = b;
	b = temp;
}

void swap(char *name1, char *name2) {

	char temp[50];
	strcpy(temp, name1);
	strcpy(name1, name2);
	strcpy(name2, temp);
}

void swap(char **name1, char **name2) {

	char *temp = *name1;
	*name1 = *name2;
	*name2 = temp;
}



void newAndDelete() {

	float **mat;
	int rows, numOfElements;

	cout << "pls enter number of rows: " << endl;
	cin >> rows;
	mat = new float *[rows];

	for (int i = 0; i < rows; i++) {
		cout << "pls enter number of elements: " << endl;
		cin >> numOfElements;
		mat[i] = new float[numOfElements];

		for (int j = 0; j < numOfElements; j++) {
			cin >> mat[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < rows; i++) {

		int size = sizeof(mat[i])/sizeof(mat[0][0]);

		for (int j = 0; j < size; j++) {
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < rows; i++) {
		delete[] mat[i];
	}
	delete[]mat;
}

int main() {

	//A.1.PAGE 49
	/*kishkashta("Zuf", 5);
	kishkashta(nullptr,5);
	kishkashta("Mor");

	//A.2.PAGE 49
	kishkashta();*/

	//B.1.PAGE 49
	/*int a = 5, b = 10;
	cout << a << " " << b << endl;
	swap(a, b);
	cout << a << " " << b << endl;


	char name1[50] = "Gutman";
	char name2[50] = "Pilosof";
	cout << name1 << " " << name2 << endl;
	swap(name1, name2);
	cout << name1 << " " << name2 << endl;


	char *name3 = name1;
	char *name4 = name2;
	cout << name3 << " " << name4 << endl;
	swap(&name3, &name4);
	cout << name3 << " " << name4 << endl;*/


	//Q4.PAGE 49
	newAndDelete();

}