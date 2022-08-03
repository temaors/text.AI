#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;

double antiPlagiarism (string text, string fragment);
int nextWordIndex(string text, int index);
bool isSeparator(char symbol);
int isMatchShingle(string text, string shingle);
string getShingle(string fragment, int index);

int main()
{				   	
	string text  = "Hello! Do you want to go for a walk with me? Yes. We can go to the luna-park. Take tickets to the ferris wheel, take a ride once. And we can buy cotton candy";
	string fragment = "Hello! Do you want";

	cout << endl;
	cout << antiPlagiarism(text, fragment);
	return 0;
}

double antiPlagiarism (string text, string fragment) {
	double matchSelections = 0;
	double allSelections = 0;
	double persent = 0.0;
	int index = 0;
	string shingle; 
	/* space to text transformation*/
	while (index >= 0) {
		shingle = getShingle(fragment, index);
		if (shingle != "0") {
			matchSelections += isMatchShingle(text, shingle);
			allSelections++;
			index = nextWordIndex(fragment, index);	
		} else break;	
	}
	
	persent = matchSelections / allSelections;
	return persent * 100;
}

string getShingle(string fragment, int index) {
	const int SHINGLE_SIZE = 2;
	int size = 0;
	int i = 0;
	string shingle;
	for (i = index; size < SHINGLE_SIZE; i++) {
		if (fragment[i] == '\0') {
			shingle += '\0';
			size++;
			break;
		}
			
		if ((isSeparator(fragment[i]) and !isSeparator(fragment[i + 1]))) {
			size++;
		}	
		shingle += fragment[i];
		
	}
	if (size < SHINGLE_SIZE) {
		return "0";
	}
	return shingle;
}

int isMatchShingle(string text, string shingle) {
	int index = 0;
	
	while (true) {
		bool notMatch = false;
		for (int is = 0; shingle[is] != '\0'; is++) {
			if(shingle[is] != text[index]) {
				notMatch = true;
				break;
			}
			index++;
		}
		index = nextWordIndex(text, index);
		if (notMatch and index < 0) {
			return 0;
		} else if (!notMatch) return 1;
	}
}

int nextWordIndex(string text, int index) {	
	for (int i = index; text[i] != '\0'; i++) {
		if(isSeparator(text[i]) and !isSeparator(text[i + 1]) and text[i + 1])
			return i + 1;
	}
	return -1;
}

bool isSeparator(char symbol) {
	char separator[] = ", !?:;.-";
	
	for (int i = 0; separator[i] != '\0'; i++) {
		if (separator[i] == symbol)
			return true;
	}
	return false;
}
